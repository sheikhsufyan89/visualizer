#include <crow.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "classes/users/StandardUser.h"
#include "classes/users/User.h"
#include "classes/users/CurrentUser.h"

// Helper function to serve static files
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

// Define CurrentUser instance for session management
CurrentUser currentUser;

// Initialize sample users
StandardUser user1("alice", "password123");
StandardUser user2("bob", "bobpassword");

// Function to parse form data
std::unordered_map<std::string, std::string> parseFormData(const std::string& body) {
    std::unordered_map<std::string, std::string> formData;
    size_t start = 0;
    while (start < body.length()) {
        size_t eqPos = body.find('=', start);
        size_t ampPos = body.find('&', start);
        std::string key = body.substr(start, eqPos - start);
        std::string value = body.substr(eqPos + 1, (ampPos == std::string::npos ? body.length() : ampPos) - eqPos - 1);
        formData[key] = value;
        start = (ampPos == std::string::npos ? body.length() : ampPos + 1);
    }
    return formData;
}

int main() {
    crow::SimpleApp app;

    // Register users
    StandardUser::registerUser("alice", "password123", "standard");
    StandardUser::registerUser("bob", "bobpassword", "standard");

    // Route to serve index.html
    CROW_ROUTE(app, "/")([](const crow::request& req, crow::response& res) {
        serveFile(res, "static/index.html", "text/html");
    });

    // Serve transaction page based on role
    CROW_ROUTE(app, "/transaction")([](const crow::request& req, crow::response& res) {
        if (currentUser.isLoggedIn() && currentUser.getRole() == "standard") {
            serveFile(res, "static/transaction.html", "text/html");
        } else {
            res.code = 403;
            res.body = "Access denied.";
            res.end();
        }
    });

    // Serve miner page
    CROW_ROUTE(app, "/miner")([](const crow::request& req, crow::response& res) {
        if (currentUser.isLoggedIn() && currentUser.getRole() == "miner") {
            serveFile(res, "static/miner.html", "text/html");
        } else {
            res.code = 403;
            res.body = "Access denied.";
            res.end();
        }
    });

    // Serve login page
    CROW_ROUTE(app, "/login")([](const crow::request& req, crow::response& res) {
        serveFile(res, "static/login.html", "text/html");
    });

    // Serve CSS files
    CROW_ROUTE(app, "/static/css/<string>")([](const crow::request& req, crow::response& res, std::string filename) {
        serveFile(res, "static/css/" + filename, "text/css");
    });

    // Serve assets (e.g., videos)
    CROW_ROUTE(app, "/assets/<string>")([](std::string filename) {
        crow::response res;
        std::ifstream video_file("assets/" + filename, std::ios::binary);
        if (video_file) {
            res.set_header("Content-Type", "video/mp4");
            res.body = std::string((std::istreambuf_iterator<char>(video_file)),
                                   std::istreambuf_iterator<char>());
        } else {
            res.code = 404;
        }
        return res;
    });

    // Login route (POST)
    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON data");
        }

        cout << User::getUser(0);
        std::string username = body["username"].s();
        std::string password = body["password"].s();

        if (User::login(username, password)) {
            for (int i = 0; i < User::getUserCount(); ++i) {
                User* user = User::getUser(i);
                if (user->getUsername() == username) {
                    currentUser.login(username, password, user->getRole());

                    if (user->getRole() == "standard") {
                        return crow::response(200, "/transaction");
                    } else if (user->getRole() == "miner") {
                        return crow::response(200, "/miner");
                    } else {
                        return crow::response(200, "/");
                    }
                }
            }
        }
        return crow::response(401, "Invalid credentials");
    });

    // Logout route (POST)
    CROW_ROUTE(app, "/logout").methods("POST"_method)([](const crow::request& req) {
        currentUser.logout();
        return crow::response(200, "Logged out successfully");
    });

    app.port(8080).multithreaded().run();
    return 0;
}
