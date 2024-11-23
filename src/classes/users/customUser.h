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

    unsigned int hashTransaction(const string& transactionData, time_t transactionTime) const {
        unsigned int hash = 0;
        string timeStr = to_string(transactionTime);
        string data = transactionData + timeStr;
        for (char ch : data) {
            hash = hash * 31 + ch;
        }

        hash ^= (hash >> 16);
        hash *= 0x85ebca6b;
        hash ^= (hash >> 13);

        return hash;
    }

    void display() const;
};

#endif
