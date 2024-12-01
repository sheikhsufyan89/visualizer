#include "SignedPool.h"
#include "SignedTransaction.h"

using namespace std;

SignedPool* SignedPool::instance = nullptr;

// SignedPool::SignedPool() : signed_count(0) {
//     for (int i = 0; i < 100; ++i) {
//         already_signed[i] = nullptr;
//     }
// }

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
            // std::cout << "Processing signed transaction: " << transaction_id << std::endl;
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



// int main() {
//     // Create 5 SignedTransaction objects
//     SignedTransaction tx1("Alice", "Bob", 500.0, 123456, "Alice's Private Key");
//     SignedTransaction tx2("Bob", "Charlie", 200.0, 654321, "Bob's Private Key");
//     SignedTransaction tx3("Charlie", "Dave", 150.0, 112233, "Charlie's Private Key");
//     SignedTransaction tx4("Dave", "Eve", 300.0, 998877, "Dave's Private Key");
//     SignedTransaction tx5("Eve", "Alice", 450.0, 334455, "Eve's Private Key");

//     // Get the instance of SignedPool
//     SignedPool* pool = SignedPool::getInstance("MySignedPool");

//     // Add transactions to the pool
//     pool->addSTransaction(&tx1);
//     pool->addSTransaction(&tx2);
//     pool->addSTransaction(&tx3);
//     pool->addSTransaction(&tx4);
//     pool->addSTransaction(&tx5);

//     // Display the pool with the added transactions
//     pool->display();

//     // Optionally, test the removal of a transaction
//     cout << "\nProcessing transaction with ID: " << tx2.getId() << endl;
//     pool->processTransaction(tx2.getId());

//     // Display the pool again after processing the transaction
//     cout << "\nAfter processing one transaction:" << endl;
//     pool->display();

//     return 0;
// }