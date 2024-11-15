#include "block.h"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

Block::Block(int index, const std::string& previousHash)
    : index(index), previousHash(previousHash), nonce(0), transactionCount(0) {
    timestamp = std::time(nullptr);  // Set the current time as the block's timestamp
}

// Adds a transaction to the block, returns false if block transaction limit is reached
bool Block::addTransaction(Transaction* tx) {
    if (transactionCount < MAX_TRANSACTIONS) {
        transactions[transactionCount++] = tx;
        return true;
    }
    return false;
}

// Concatenate block data to create a unique string for hashing
std::string Block::getData() const {
    std::stringstream ss;
    ss << index << previousHash << timestamp << nonce;
    for (int i = 0; i < transactionCount; ++i) {
        ss << transactions[i]->getId();  // You might want to add more transaction details here
    }
    return ss.str();
}

// Display block information and transactions
void Block::display() const {
    std::cout << "Block Index: " << index << "\n";
    std::cout << "Hash: " << hash << "\n";
    std::cout << "Previous Hash: " << previousHash << "\n";
    std::cout << "Timestamp: " << timestamp << "\n";
    std::cout << "Nonce: " << nonce << "\n";
    std::cout << "Transactions:\n";
    for (int i = 0; i < transactionCount; ++i) {
        transactions[i]->display();  // Assuming Transaction has a display method
    }
    std::cout << "---------------------------------\n";
}
