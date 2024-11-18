#ifndef PENDING_TRANSACTION_POOL_H
#define PENDING_TRANSACTION_POOL_H

#include <string>
#include <iostream>
#include "../entity.h"

class Transaction;

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
};

#endif 
