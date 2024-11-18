#include <crow.h>
#include <fstream>
#include <sstream>
#include "classes/users/StandardUser.h"
#include "classes/users/User.h"
#include "classes/users/CurrentUser.h"
#include "classes/users/CustomUser.h"
#include "classes/transactions/Transaction.h"
#include "classes/transactions/pendingTransactionPool.h"

void serveFile(crow::response& res, const std::string& filePath, const std::string& contentType) {
    std::ifstream file(filePath);
    if (!file) {
        res.code = 404;
        res.body = "File not found";
    } else {
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.body = buffer.str();
        res.set_header("Content-Type", contentType);
    }
    res.end();
}

PendingTransactionPool* txPool = PendingTransactionPool::getInstance();
CurrentUser currentUser;

const int MAX_USERS = 10;
StandardUser standardUsers[MAX_USERS] = {
    StandardUser("user1", "password1"),
    StandardUser("user2", "password2")
};

CustomUser customUsers[MAX_USERS] = {
    CustomUser("custom1", "password1"),
    CustomUser("custom1", "password2")
};
// User customUsers[MAX_USERS]; 
// User minerUsers[MAX_USERS];  
int standardUserCount = 2;
int customUserCount = 2;
// int minerUserCount = 0;



int main() {
    crow::SimpleApp app;

    

    CROW_ROUTE(app, "/")([](const crow::request& req, crow::response& res) {
        serveFile(res, "static/index.html", "text/html");
    });

    CROW_ROUTE(app, "/currentUser")([](const crow::request& req, crow::response& res) {
    if (currentUser.isLoggedIn()) {
        crow::json::wvalue response_data;
        response_data["username"] = currentUser.getUsername();
        response_data["role"] = currentUser.getRole();
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.body = response_data.dump();  
        res.end();
    } else {
        res.code = 401;
        res.body = "User not logged in";
        res.end();
    }
});


    

    CROW_ROUTE(app, "/transaction")([](const crow::request& req, crow::response& res) {
        if (currentUser.isLoggedIn()) {
            serveFile(res, "static/transaction.html", "text/html");
        } else {
            res.code = 403;
            res.body = "Access denied.";
            res.end();
        }
    });

    CROW_ROUTE(app, "/miner")([](const crow::request& req, crow::response& res) {
        if (currentUser.isLoggedIn() && currentUser.getRole() == "miner") {
            serveFile(res, "static/miner.html", "text/html");
        } else {
            res.code = 403;
            res.body = "Access denied.";
            res.end();
        }
    });

   CROW_ROUTE(app, "/login")([](const crow::request& req, crow::response& res) {
    if (currentUser.isLoggedIn()) {
        if (currentUser.getRole() == "standard" || currentUser.getRole() == "custom") {
            res.redirect("/transaction");
        } else if (currentUser.getRole() == "miner") {
            res.redirect("/miner");
        }
    } else {
        serveFile(res, "static/login.html", "text/html");
    }
    res.end();
});



    CROW_ROUTE(app, "/static/css/<string>")([](const crow::request& req, crow::response& res, std::string filename) {
        serveFile(res, "static/css/" + filename, "text/css");
    });

    // CROW_ROUTE(app, "/assets/<string>")([](std::string filename) {
    //     crow::response res;
    //     std::ifstream video_file("assets/" + filename, std::ios::binary);
    //     if (video_file) {
    //         res.set_header("Content-Type", "video/mp4");
    //         res.body = std::string((std::istreambuf_iterator<char>(video_file)),
    //                                std::istreambuf_iterator<char>());
    //     } else {
    //         res.code = 404;
    //     }
    //     return res;
    // });
    CROW_ROUTE(app, "/assets/<string>")([](std::string filename) {
    crow::response res;
    std::ifstream file("assets/" + filename, std::ios::binary);
    
    auto ends_with = [](const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    };

    if (file) {
        // Set the correct MIME type based on the file extension
        if (ends_with(filename, ".mp3")) {
            res.set_header("Content-Type", "audio/mpeg");
        } else if (ends_with(filename, ".mp4")) {
            res.set_header("Content-Type", "video/mp4");
        } else {
            res.set_header("Content-Type", "application/octet-stream");
        }

        // Read the file content and set the response body
        res.body = std::string((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
        res.code = 200;
    } else {
        res.code = 404;
        res.body = "File not found.";
    }
    
    return res;
});


    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON data");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();
        std::string role = body["role"].s();
        

        if (role == "standard") {
            for (int i = 0; i < standardUserCount; ++i) {
                if (standardUsers[i].getUsername() == username && standardUsers[i].getPassword() == password) {
                    crow::json::wvalue response_data;
                    response_data["username"] = username;
                    response_data["password"] = password;
                    response_data["role"] = role;
                    response_data["redirect_url"] = "transaction";
                    currentUser.login(username, password, role);
                    return crow::response(200, response_data);
                }
            }
        } else if (role == "custom") {
            for (int i = 0; i < customUserCount; ++i) {
                if (customUsers[i].getUsername() == username && customUsers[i].getPassword() == password) {
                    crow::json::wvalue response_data;
                    response_data["username"] = username;
                    response_data["password"] = password;
                    response_data["role"] = role;
                    response_data["redirect_url"] = "transaction";
                    currentUser.login(username, password, role);
                    return crow::response(200, response_data);
                }
            }
        } else if (role == "miner") {
        }

        return crow::response(401, "Invalid credentials");
    });

    CROW_ROUTE(app, "/logout").methods("POST"_method)([](const crow::request& req) {
        currentUser.logout();
        return crow::response(200, "Logged out successfully");
    });

CROW_ROUTE(app, "/addTransaction").methods("POST"_method)([](const crow::request& req) {
    auto body = crow::json::load(req.body);
    
    if (!body) {
        std::cerr << "Invalid JSON: " << req.body << std::endl;
        return crow::response(400, "Invalid JSON data");
    }

    std::string sender = body["sender"].s();
    std::string recipient = body["recipient"].s();
    double amount = body["amount"].d();

    Transaction* tx = new Transaction(sender, recipient, amount);
    if (txPool->addTransaction(tx)) {
        return crow::response(200, "Transaction created successfully");
    } else {
        return crow::response(400, "Transaction failed");
    }
});

    // CROW_ROUTE(app, "/pendingTransactions")([] {
    //     PendingTransactionPool* pool = PendingTransactionPool::getInstance();
    //     crow::json::wvalue response;
    //     int index = 0;

    //     for (int i = 0; i < pool->getPendingCount(); ++i) {
    //         Transaction* tx = pool->getTransactionAt(i); 
    //         if (tx) {
    //             crow::json::wvalue transactionJson;
    //             transactionJson["id"] = tx->getId();
    //             transactionJson["sender"] = tx->getSender();
    //             transactionJson["recipient"] = tx->getRecipient();
    //             transactionJson["amount"] = tx->getAmount();
    //             response[index++] = std::move(transactionJson);
    //         }
    //     }

    //     return crow::response(200, response);
    // });







    app.port(8080).multithreaded().run();
    return 0;
}
