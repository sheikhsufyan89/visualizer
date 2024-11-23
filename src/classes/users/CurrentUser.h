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


    unsigned int calculateHash(const string& transactionData, time_t transactionTime) {
        if (role == "standard") {
            return currentStandardUser.hashTransaction(transactionData, transactionTime); 
        } else if (role == "custom") {
            return currentCustomUser.hashTransaction(transactionData, transactionTime); 
        }
        return 0; 
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
