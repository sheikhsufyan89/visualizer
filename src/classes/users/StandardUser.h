#ifndef STANDARDUSER_H
#define STANDARDUSER_H

#include "User.h"

class StandardUser : public User {
private:

public:
   
    StandardUser(const std::string& username, const std::string& password)
        : User(username, password, "standard") {}

    unsigned int hashTransaction(const std::string& transactionData, time_t transactionTime) const;

    void display() const;
};

#endif
