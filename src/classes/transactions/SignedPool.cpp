#include "SignedPool.h"
#include "SignedTransaction.h"

using namespace std;

SignedPool* SignedPool::instance = nullptr;


bool SignedPool::addSTransaction(SignedTransaction* stx) {
    if (signed_count < 100) {
        already_signed[signed_count++] = stx;
        return true;
    }
    return false;
}

bool SignedPool::deleteSTransaction(const string& transaction_id) {
    for (int i = 0; i < signed_count; ++i) {
        if (already_signed[i]->getId() == transaction_id) {
            for (int j = i; j < signed_count - 1; ++j) {
                already_signed[j] = already_signed[j + 1];
            }
            --signed_count;
            return true;
        }
    }
    return false;
}

void SignedPool::processTransaction(const string& transaction_id) {
    for (int i = 0; i < signed_count; ++i) {
        if (already_signed[i]->getId() == transaction_id) {
            deleteSTransaction(transaction_id);
            break;
        }
    }
}

void SignedPool::display() const {
    std::cout << "Signed Transaction Pool ID: " << getId() << std::endl;
    std::cout << "Signed Transactions: " << std::endl;
    for (int i = 0; i < signed_count; ++i) {
        already_signed[i]->display();
    }
    cout << "----------------------------------------------------------------------------------------------" << endl;
}

int SignedPool::getPendingCount() {
    return signed_count;
}


void SignedPool::clearPool() {
    for (int i = 0; i < signed_count; ++i) {
        delete already_signed[i]; 
        already_signed[i] = nullptr; 
    }
    signed_count = 0; 
}