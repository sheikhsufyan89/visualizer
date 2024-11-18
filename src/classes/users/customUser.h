#ifndef CUSTOMUSER_H
#define CUSTOMUSER_H

#include "User.h"

using namespace std;
class CustomUser : public User {
private:

public:

    CustomUser() : User("", "", "custom") {}
   
    CustomUser(const string& username, const string& password)
        : User(username, password, "custom") {}

    // unsigned int hashTransaction(const string& transactionData, time_t transactionTime) const;

    void display() const;
};

#endif
