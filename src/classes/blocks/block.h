#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "../transactions/transaction.h"  

const int MAX_TRANSACTIONS = 100;

using namespace std;

class Block {
private:
    int index;                          // Block's position in the blockchain
    string hash;                   // Hash of the current block
    string previousHash;           // Hash of the previous block
    int nonce;                          // Nonce for proof of work
    Transaction* transactions[MAX_TRANSACTIONS];  // Array to hold transactions
    int transactionCount;               // Tracks the number of transactions in the block
    long timestamp;                     // Timestamp for block creation

public:
    Block(int index, const string& previousHash);

    // Getter methods
    int getIndex() const { return index; }
    const string& getHash() const { return hash; }
    const string& getPreviousHash() const { return previousHash; }
    int getNonce() const { return nonce; }
    long getTimestamp() const { return timestamp; }
    int getTransactionCount() const { return transactionCount; }

    // Setter methods
    void setHash(const std::string& newHash) { hash = newHash; }
    void incrementNonce() { nonce++; }

    // Method to add a transaction to the block
    bool addTransaction(Transaction* tx);

    // Method to get block data for hashing
    string getData() const;

    // Display block information
    void display() const;
};

#endif // BLOCK_H
