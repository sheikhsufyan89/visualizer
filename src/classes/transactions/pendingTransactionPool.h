#ifndef PENDING_TRANSACTION_POOL_H
#define PENDING_TRANSACTION_POOL_H

#include <string>
#include <iostream>
#include "../entity.h" 
#include "transaction.h"


using namespace std;

class PendingTransactionPool : public Entity {
private:
    Transaction* pendingTransactions[100];
    int pendingCount; // tracks current number of pending transactions in the pool.
    static PendingTransactionPool* instance; // ensures there is only one instance of this class.
    PendingTransactionPool(const string& id) : Entity(id), pendingCount(0) {}

public:
    // Get the singleton instance
    static PendingTransactionPool* getInstance(const string& id = "default_pool_id") {
        if (!instance) {
            instance = new PendingTransactionPool(id);
        }
        return instance;
    }

    bool addTransaction(Transaction* tx);
    bool removeTransaction(const std::string& transactionId);

    // Optional method to simulate processing a transaction (moving to blockchain)
    void processTransaction(const std::string& transactionId);
    void display() const override;
};

#endif