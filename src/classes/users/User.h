#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

class User {
public:
    User(){}

    User(const string& username, const string& password, const string& role)
        : username(username), password(password), role(role) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getRole() const {
        return role;
    }

protected:
    string username;
    string password;
    string role;
};

#endif 
