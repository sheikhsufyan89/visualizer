#ifndef VALIDATEDTRANSACTION_H
#define VALIDATEDTRANSACTION_H

#include <string>
#include "../entity.h"
#include "SignedTransaction.h"

class ValidatedTransaction : public Entity {
private:
    std::string sender;
    std::string receiver;
    double amount;
    time_t timestamp;

public:
    ValidatedTransaction(const std::string& id, const std::string& sender, const std::string& receiver, 
                         double amount, time_t timestamp);

    void display() const override;

    // Accessor methods
    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    time_t getTimestamp() const;
};

#endif
