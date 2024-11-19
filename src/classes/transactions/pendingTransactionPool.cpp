#include "pendingTransactionPool.h"
#include "transaction.h" 

using namespace std;

PendingTransactionPool* PendingTransactionPool::instance = nullptr;

bool PendingTransactionPool::addTransaction(Transaction* tx) {
    if (pendingCount < 100) {
        pendingTransactions[pendingCount++] = tx;
        return true;
    }
    return false;
}

bool PendingTransactionPool::removeTransaction(const std::string& transactionId) {
    for (int i = 0; i < pendingCount; ++i) {
        if (pendingTransactions[i]->getId() == transactionId) {
            for (int j = i; j < pendingCount - 1; ++j) {
                pendingTransactions[j] = pendingTransactions[j + 1];
            }
            --pendingCount;
            return true;
        }
    }
    return false;  
}

void PendingTransactionPool::processTransaction(const std::string& transactionId) {
    for (int i = 0; i < pendingCount; ++i) {
        if (pendingTransactions[i]->getId() == transactionId) {
            std::cout << "Processing transaction: " << transactionId << std::endl;
            removeTransaction(transactionId);
            break;
        }
    }
}

void PendingTransactionPool::display() const {
    std::cout << "Pending Transaction Pool ID: " << getId() << std::endl;
    std::cout << "Pending Transactions: " << std::endl;
    for (int i = 0; i < pendingCount; ++i) {
        pendingTransactions[i]->display();
    }
}

int PendingTransactionPool::getPendingCount(){
    return pendingCount;
}
