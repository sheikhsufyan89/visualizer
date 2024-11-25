// #include "ValidationPool.h"

// using namespace std;

// ValidationPool* ValidationPool::instance = nullptr;

// // bool ValidationPool::addValidatedTransaction(SignedTransaction* vtx) {
// //     if (validated_count < 100) {
// //         validated_transactions[validated_count++] = vtx;
// //         return true;
// //     }
// //     return false; 
// // }

// bool ValidationPool::deleteValidatedTransaction(const string& transaction_id) {
//     for (int i = 0; i < validated_count; ++i) {
//         if (validated_transactions[i]->getId() == transaction_id) {
//             for (int j = i; j < validated_count - 1; ++j) {
//                 validated_transactions[j] = validated_transactions[j + 1];
//             }
//             --validated_count;
//             return true;
//         }
//     }
//     return false; 
// }

// void ValidationPool::display() const {
//     cout << "Validation Pool ID: " << getId() << endl;
//     cout << "Validated Transactions: " << endl;
//     for (int i = 0; i < validated_count; ++i) {
//         validated_transactions[i]->display();
//     }
// }

















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
    if (validated_count == 0) {
        cout << "Validation Pool is empty." << endl;
    } else {
        cout << "Validation Pool ID: " << getId() << endl;
        cout << "Validated Transactions: " << endl;
        for (int i = 0; i < validated_count; ++i) {
            validated_transactions[i]->display();
        }
    }
    cout << "----------------------------------------------------------------------------------------------" << endl;
}












//further functions added by khadeer to comply the class start here


bool ValidationPool::addValidatedTransaction(ValidatedTransaction* vtx) {
    if (validated_count < 100) {
        validated_transactions[validated_count++] = vtx;
        return true;
    } else {
        cout << "Validation pool is full. Cannot add more transactions." << endl;
        return false;
    }
}


ValidatedTransaction* ValidationPool::getTransaction(int index) const {
    if (index >= 0 && index < 100) { // Assuming a fixed array size of 100
        return validated_transactions[index];
    }
    return nullptr;
}





ValidationPool* ValidationPool::getInstance(const string& id) {
    if (instance == nullptr) {
        instance = new ValidationPool(id);  // Create the instance if it doesn't exist
    }
    return instance;
}

int ValidationPool::getValidatedCount() const {
    return validated_count;
}


void ValidationPool::clear() {
    validated_count = 0;
}

ValidationPool::~ValidationPool() {
    for (int i = 0; i < validated_count; ++i) {
        delete validated_transactions[i];
    }
    delete instance;
    validated_count = 0;
}


//further functions added by khadeer to comply the class end here