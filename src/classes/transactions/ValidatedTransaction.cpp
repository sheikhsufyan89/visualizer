#include "ValidatedTransaction.h"
#include "SignedTransaction.h"
#include <iostream>

ValidatedTransaction::ValidatedTransaction(const std::string& id, const std::string& sender, 
                                           const std::string& receiver, double amount, time_t timestamp)
    : Entity(id), sender(sender), receiver(receiver), amount(amount), timestamp(timestamp) {}

void ValidatedTransaction::display() const {
    std::cout << "Transaction ID: " << getId() 
              << ", Sender: " << sender 
              << ", Receiver: " << receiver 
              << ", Amount: " << amount 
              << ", Timestamp: " << timestamp << std::endl;
}


std::string ValidatedTransaction::getSender() const { return sender; }
std::string ValidatedTransaction::getReceiver() const { return receiver; }
double ValidatedTransaction::getAmount() const { return amount; }
time_t ValidatedTransaction::getTimestamp() const { return timestamp; }