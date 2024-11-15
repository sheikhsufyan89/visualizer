#include "User.h"

#include <iostream>

User* User::users[MAX_USERS] = { nullptr }; 
int User::userCount = 0;  




bool User::registerUser(const std::string& username, const std::string& password, const std::string& role) {
    if (userCount < MAX_USERS) {
        users[userCount] = new User(username, password, role);
        ++userCount;
        return true;
    }
    return false;  // No space for more users
}

bool User::login(const std::string& username, const std::string& password) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i]->getUsername() == username && users[i]->password == password) {
            return true;  // Valid login
        }
    }
    return false;  // Invalid login
}

int User::getUserCount() {
    return userCount;
}

// Getter for users by index
User* User::getUser(int index) {
    if (index >= 0 && index < userCount) {
        return users[index];
    }
    return nullptr;
}


