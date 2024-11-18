#ifndef STANDARDUSER_H
#define STANDARDUSER_H

#include "User.h"

using namespace std;
class StandardUser : public User {
private:

public:

    StandardUser() : User("", "", "standard") {}
   
    StandardUser(const string& username, const string& password)
        : User(username, password, "standard") {}

    unsigned int hashTransaction(const string& transactionData, time_t transactionTime) const;

    void display() const;
};

#endif
