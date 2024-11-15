#ifndef CURRENT_USER_H
#define CURRENT_USER_H
#include <string>


using namespace std;
class CurrentUser {
public:
    void login(const string& uname, const string& pass, const string& userRole) {
        username = uname;
        password = pass;
        role = userRole;
        loggedIn = true;
    }

    void logout() {
        username.clear();
        password.clear();
        role.clear();
        loggedIn = false;
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

private:
    string username;
    string password;
    string role;
    bool loggedIn = false;
};

#endif