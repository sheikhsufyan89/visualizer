#ifndef CURRENT_USER_H
#define CURRENT_USER_H
#include <string>
#include <functional>
#include "StandardUser.h"
#include "CustomUser.h"

using namespace std;

class CurrentUser {
public:
    void login(const string& uname, const string& pass, const string& userRole) {
        username = uname;
        password = pass;
        role = userRole;
        loggedIn = true;

        // Initialize the user based on role
        if (role == "standard") {
            currentStandardUser = StandardUser(username, password);
        } else if (role == "custom") {
            currentCustomUser = CustomUser(username, password);
        }
    }

    void logout() {
        username.clear();
        password.clear();
        role.clear();
        loggedIn = false;
        currentStandardUser = StandardUser("", "");
        currentCustomUser = CustomUser("", "");
    }

    string getRole() const {
        return role;
    }

    bool isLoggedIn() const {
        return loggedIn;
    }

    string getUsername() const {
        return username;
    }

    // Method to calculate hash based on user role
    int calculateHash(const string& transactionData, time_t transactionTime) {
        if (role == "standard") {
            return currentStandardUser.hashTransaction(transactionData, transactionTime); 
        } else if (role == "custom") {
            // Assuming CustomUser has its own hash method
            return currentCustomUser.hashTransaction(transactionData, transactionTime); 
        }
        return 0; // Default case if no role matches
    }

private:
    string username;
    string password;
    string role;
    bool loggedIn = false;
    
    StandardUser currentStandardUser;
    CustomUser currentCustomUser;
};

#endif
