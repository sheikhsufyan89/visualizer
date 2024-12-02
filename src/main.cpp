#include <crow.h>
#include <fstream>
#include <sstream>
#include "classes/users/StandardUser.h"
#include "classes/users/User.h"
#include "classes/users/CurrentUser.h"
#include "classes/users/CustomUser.h"
#include "classes/transactions/Transaction.h"
#include "classes/transactions/PendingTransactionPool.h"
#include "classes/transactions/SignedPool.h"
#include "classes/transactions/SignedTransaction.h"
#include "classes/miners/miner.h"
#include "classes/Chain/BlockChain.h"
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




void writeCodeToFile(const std::string& hashFunction, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "#include <iostream>\n"
             << "#include <string>\n"
             << "#include <ctime>\n"
            //  << "unsigned int hashTransaction(const std::string& transactionData, time_t transactionTime) {\n"
             << hashFunction << "\n"
            //  << "}\n"
             << "int main() {\n"
             << "    std::string transactionData = \"SampleData\";\n"
             << "    time_t transactionTime = 123456789;\n"
             << "    try {\n"
             << "        std::cout << hashTransaction(transactionData, transactionTime) << std::endl;\n"
             << "    } catch (...) {\n"
             << "        return 1; // Indicate an error in the hash function\n"
             << "    }\n"
             << "    return 0;\n"
             << "}\n";
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing hash function.\n";
        exit(1);
    }
}

void writeHashFunctionToFile(const std::string& hashFunction, const std::string& filename, const std::string& transactionData, time_t transactionTime) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "#include <iostream>\n"
             << "#include <string>\n"
             << "#include <ctime>\n"
             << hashFunction << "\n"
             << "int main() {\n"
             << "    std::string transactionData = \"" << transactionData << "\";\n"
             << "    time_t transactionTime = " << transactionTime << ";\n"
             << "    try {\n"
             << "        std::cout << hashTransaction(transactionData, transactionTime) << std::endl;\n"
             << "    } catch (...) {\n"
             << "        return 1; // Indicate an error in the hash function\n"
             << "    }\n"
             << "    return 0;\n"
             << "}\n";
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing hash function.\n";
        exit(1);
    }
}

int compileAndExecute(const std::string& cppFile, const std::string& executable) {
    std::string command = "g++ " + cppFile + " -o " + executable;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Compilation failed.\n";
        exit(1);
    }

    command = executable + ".exe > output.txt";
    result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Execution failed.\n";
        exit(1);
    }

    return 0;
}

bool compileCode(const std::string& cppFile) {
    std::string command = "g++ -o test_program " + cppFile; 
    int result = std::system(command.c_str());
    return result == 0; 
}


bool validateHashFunction(const std::string& hashFunction) {
    if (hashFunction.find("unsigned int hashTransaction(const std::string& transactionData, time_t timestamp)") == std::string::npos ||
        hashFunction.find("unsigned int") == std::string::npos) {
        std::cerr << "Error: Incorrect function signature or return type.\n";
        return false;
    }

    const std::string cppFile = "user_hash_function.cpp";
    writeCodeToFile(hashFunction, cppFile);

    if (!compileCode(cppFile)) {
        std::cerr << "Error: Compilation failed due to syntax or other issues.\n";
        return false;
    }

    return true; 
}



unsigned int readOutputFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open output file for reading.\n";
        exit(1);
    }

    unsigned int output = 0;
    file >> output; 

    if (file.fail()) {
        std::cerr << "Error: Failed to read unsigned int from file.\n";
        exit(1);
    }

    file.close();
    return output;
}

unsigned int executeHashFunction(const string& hashFunction, const string& transactionData, time_t transactionTime) {
    string cppFile = "hash_function_execution.cpp";
    string executable = "hash_program";
    string outputFile = "output.txt";
    writeHashFunctionToFile(hashFunction, cppFile, transactionData, transactionTime);
    compileAndExecute(cppFile, executable);
    unsigned int output = readOutputFromFile(outputFile);
    return output;
}

PendingTransactionPool* txPool = PendingTransactionPool::getInstance();
SignedPool* sxPool = SignedPool::getInstance();
ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");

BlockChain Blockchain(1);

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

Miner miners[MAX_USERS]= {
    Miner("miner1", "password1", 1),
    Miner("miner2", "password2", 2)
};



int standardUserCount = 2;
int customUserCount = 2;
int minerUserCount = 2;



int main() {
    crow::SimpleApp app;

    Transaction* tx1 = new Transaction("user1", "user2", 100.0);
    Transaction* tx2 = new Transaction("user2", "user1", 50.0);
    Transaction* tx3 = new Transaction("custom1", "user1", 200.0);

    txPool->addTransaction(tx1);
    txPool->addTransaction(tx2);
    txPool->addTransaction(tx3);

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

CROW_ROUTE(app, "/static/css/<string>")
([](const crow::request& req, crow::response& res, std::string filename) {
    serveFile(res, "static/css/" + filename, "text/css");
});

CROW_ROUTE(app, "/assets/<string>")
([](std::string filename) {
    crow::response res;
    std::ifstream file("assets/" + filename, std::ios::binary);
    auto ends_with = [](const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    };

    if (file) {
        if (ends_with(filename, ".mp3")) {
            res.set_header("Content-Type", "audio/mpeg");
        } else if (ends_with(filename, ".mp4")) {
            res.set_header("Content-Type", "video/mp4");
        } else if (ends_with(filename, ".js")) {
            res.set_header("Content-Type", "application/javascript");
        } else if (ends_with(filename, ".css")) {
            res.set_header("Content-Type", "text/css");
        } else if (ends_with(filename, ".html")) {
            res.set_header("Content-Type", "text/html");
        } else {
            res.set_header("Content-Type", "application/octet-stream");
        }

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
            for (int i = 0; i < minerUserCount; ++i) {
                if (miners[i].getUsername() == username && miners[i].getPassword() == password) {
                    crow::json::wvalue response_data;
                    response_data["username"] = username;
                    response_data["password"] = password;
                    response_data["role"] = role;
                    response_data["redirect_url"] = "miner";
                    currentUser.login(username, password, role);
                    return crow::response(200, response_data);
                }
            }
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
        crow::json::wvalue response;
        response["message"] = "Transaction created successfully";
        response["transactionId"] = tx->getId();  
        return crow::response(200, response);
    } else {
        crow::json::wvalue errorResponse;
        errorResponse["message"] = "Transaction failed";
        return crow::response(400, errorResponse);
    }
});

CROW_ROUTE(app, "/hash").methods("POST"_method)([](const crow::request& req) {
    auto body = crow::json::load(req.body);

    string id = body["transactionId"].s();
    string sender = body["sender"].s();
    string receiver = body["receiver"].s();
    string signed_by = body["signed_by"].s();
    double amount = body["amount"].d();
    string hashFunction = body["hashfunction"].s();

    string transactionData = signed_by + receiver + to_string(amount);
    time_t timestamp = txPool->getTransactionTimestamp(id);

    unsigned int hash;
    if (!hashFunction.empty() && currentUser.getRole() == "custom") {
        string cppFile = "hash_function_test.cpp";
        if (validateHashFunction(hashFunction)) {
            hash = executeHashFunction(hashFunction, transactionData, timestamp);
        } else {
            return crow::response(400, "Invalid hash function");
        }
    } else {
        hash = currentUser.calculateHash(transactionData, timestamp);
    }
    SignedTransaction* sx = new SignedTransaction(id, sender, receiver, amount, hash, signed_by, timestamp);
    sxPool->addSTransaction(sx);

    crow::json::wvalue response;
    response["id"] = id;
    response["sender"] = sender;
    response["recipient"] = receiver;
    response["amount"] = amount;
    response["signed_by"] = signed_by;
    response["hash"] = hash;
    txPool->removeTransaction(id);

    return crow::response(200, response);
});

    CROW_ROUTE(app, "/pendingTransactions")([] {
        PendingTransactionPool* pool = PendingTransactionPool::getInstance();
        crow::json::wvalue response;
        int index = 0;

        for (int i = 0; i < pool->getPendingCount(); ++i) {
            Transaction* tx = pool->getTransactionAt(i); 
            if (tx) {
                crow::json::wvalue transactionJson;
                transactionJson["id"] = tx->getId();
                transactionJson["sender"] = tx->getSender();
                transactionJson["receiver"] = tx->getReceiver();
                transactionJson["amount"] = tx->getAmount();
                response[index++] = std::move(transactionJson);
            }
        }

        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/signedTransactions")([] {
        SignedPool* pool = SignedPool::getInstance();
        crow::json::wvalue response;
        int index = 0;

        for (int i = 0; i < pool->getPendingCount(); ++i) {
            SignedTransaction* tx = pool->getTransaction(i); 
            if (tx) {
                crow::json::wvalue transactionJson;
                transactionJson["id"] = tx->getId();
                transactionJson["sender"] = tx->getSender();
                transactionJson["receiver"] = tx->getReceiver();
                transactionJson["amount"] = tx->getAmount();
                transactionJson["signed_by"] = tx->getSignedBy();
                transactionJson["hash"] = tx->getHashVal();
                transactionJson["time"] = tx->getTimeStamp();
                
                response[index++] = std::move(transactionJson);
            }
        }
        

        return crow::response(200, response);
    });



  CROW_ROUTE(app, "/validate").methods("POST"_method)([]() {
    crow::json::wvalue response;
    string result = currentUser.ValidateAndAddTransactions(sxPool);
    sxPool->clearPool();
    response["result"] = result;  
    response["status"] = "success";  
    return crow::response{response};  
});

    CROW_ROUTE(app, "/validatedTransactions")([] {
    ValidationPool* pool = ValidationPool::getInstance("MyValidationPool");
    crow::json::wvalue response;
    int index = 0;

    for (int i = 0; i < pool->getValidatedCount(); ++i) {
        ValidatedTransaction* tx = pool->getTransaction(i); 
        if (tx) {
            crow::json::wvalue transactionJson;
            transactionJson["id"] = tx->getId();
            transactionJson["sender"] = tx->getSender();
            transactionJson["receiver"] = tx->getReceiver();
            transactionJson["amount"] = tx->getAmount();
            response[index++] = std::move(transactionJson);
        }
    }
    return crow::response(200, response);  
    });

CROW_ROUTE(app, "/addBlock").methods("POST"_method)([]() {
    crow::json::wvalue response;

    vector<string> txData1;
    for (int i = 0; i < validationPool->getValidatedCount(); ++i) {
        ValidatedTransaction* tx = validationPool->getTransaction(i);
        if (tx != nullptr) {
            txData1.push_back(tx->getId() + ": " + tx->getSender() + " -> " + tx->getReceiver() + ": " + to_string(tx->getAmount()));
        }
    }
    string result = Blockchain.addBlock(txData1);
    validationPool->clearPool();
    response["result"] = result;  
    response["status"] = "success";  
    return crow::response{response};  
});


// CROW_ROUTE(app, "/blockchain")([] {
//     crow::json::wvalue response; 
    
    

//     // Iterate over the blockchain and collect block data
//     for (const Block& block : Blockchain.getChain()) {
//         crow::json::wvalue blockData;

//         blockData["index"] = block.getIndex();
//         blockData["data"] = block.getData();
//         blockData["previousHash"] = block.getPreviousHash();
//         blockData["hash"] = block.getHash();
//         blockData["nonce"] = block.getNonce();

//         // Push block data into the blocks array
//         blocks.push_back(blockData);
//     }

//     // Add the blocks data to the response
//     response["blocks"] = blocks;

//     return crow::response{response};
// });

CROW_ROUTE(app, "/blockchain")([] {
    crow::json::wvalue response;
    int index = 0; 
    for (const Block& block : Blockchain.getChain()) {
        crow::json::wvalue blockData;
        blockData["index"] = block.getIndex();
        blockData["data"] = block.getData();
        blockData["previousHash"] = block.getPreviousHash();
        blockData["hash"] = block.getHash();
        blockData["nonce"] = block.getNonce();
        response[index++] = std::move(blockData);
    }
    return crow::response{response};
});



    

    app.port(8080).multithreaded().run();
    return 0;
}



