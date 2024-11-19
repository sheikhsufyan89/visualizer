#include "ValidationPool.h"

using namespace std;

ValidationPool* ValidationPool::instance = nullptr;

// bool ValidationPool::addValidatedTransaction(SignedTransaction* vtx) {
//     if (validated_count < 100) {
//         validated_transactions[validated_count++] = vtx;
//         return true;
//     }
//     return false; 
// }

bool ValidationPool::deleteValidatedTransaction(const string& transaction_id) {
    for (int i = 0; i < validated_count; ++i) {
        if (validated_transactions[i]->getId() == transaction_id) {
            for (int j = i; j < validated_count - 1; ++j) {
                validated_transactions[j] = validated_transactions[j + 1];
            }
            --validated_count;
            return true;
        }
    }
    return false; 
}

void ValidationPool::display() const {
    cout << "Validation Pool ID: " << getId() << endl;
    cout << "Validated Transactions: " << endl;
    for (int i = 0; i < validated_count; ++i) {
        validated_transactions[i]->display();
    }
}
