#ifndef PENDING_TRANSACTION_POOL_H
#define PENDING_TRANSACTION_POOL_H

#include <string>
#include <iostream>
#include "../entity.h"
#include "Transaction.h"

using namespace std;

class PendingTransactionPool : public Entity {
private:
    Transaction* pendingTransactions[100];
    int pendingCount; 
    static PendingTransactionPool* instance; 
    PendingTransactionPool(const string& id) : Entity(id), pendingCount(0) {}

public:
    static PendingTransactionPool* getInstance(const string& id = "default_pool_id") {
        if (!instance) {
            instance = new PendingTransactionPool(id);
        }
        return instance;
    }

    bool addTransaction(Transaction* tx);
    bool removeTransaction(const string& transactionId);
    void processTransaction(const string& transactionId);
    int getPendingCount();
    Transaction* getTransactionAt(int index) const {
        if (index >= 0 && index < pendingCount) {
            return pendingTransactions[index];
        }
        return nullptr;
    }
    void display() const override;
    time_t getTransactionTimestamp(const string& transactionId) const {
    for (int i = 0; i < pendingCount; ++i) {
        if (pendingTransactions[i]->getId() == transactionId) {
            return pendingTransactions[i]->getTimeStamp();
        }
    }
    throw runtime_error("Transaction with ID " + transactionId + " not found.");
}
};

#endif 
