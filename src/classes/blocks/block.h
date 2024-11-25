// #ifndef BLOCK_H
// #define BLOCK_H

// #include <string>
// #include "../transactions/transaction.h"  

// const int MAX_TRANSACTIONS = 100;

// using namespace std;

// class Block {
// private:
//     int index;                          // Block's position in the blockchain
//     string hash;                   // Hash of the current block
//     string previousHash;           // Hash of the previous block
//     int nonce;                          // Nonce for proof of work
//     Transaction* transactions[MAX_TRANSACTIONS];  // Array to hold transactions
//     int transactionCount;               // Tracks the number of transactions in the block
//     long timestamp;                     // Timestamp for block creation

// public:
//     Block(int index, const string& previousHash);

//     // Getter methods
//     int getIndex() const { return index; }
//     const string& getHash() const { return hash; }
//     const string& getPreviousHash() const { return previousHash; }
//     int getNonce() const { return nonce; }
//     long getTimestamp() const { return timestamp; }
//     int getTransactionCount() const { return transactionCount; }

//     // Setter methods
//     void setHash(const std::string& newHash) { hash = newHash; }
//     void incrementNonce() { nonce++; }

//     // Method to add a transaction to the block
//     bool addTransaction(Transaction* tx);

//     // Method to get block data for hashing
//     string getData() const;

//     // Display block information
//     void display() const;
// };

// #endif // BLOCK_H










// #ifndef BLOCK_H
// #define BLOCK_H

// #include <string>

// class Block {
// private:
//     int index;
//     std::string data;
//     std::string previousHash;
//     int nonce;
//     std::string hash;

// public:
//     Block(int idx, std::string blockData, std::string prevHash);
//     std::string computeHash();
//     void setNonce(int n);
//     int getNonce() const;
//     void setHash(const std::string& h);
//     std::string getHash() const;
//     int getIndex() const;
//     std::string getData() const;
//     std::string getPreviousHash() const;
// };

// #endif







#ifndef BLOCK_H
#define BLOCK_H

// #pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include "../transactions/SignedPool.h"
#include "../transactions/SignedTransaction.h"

class Block{
    private:
        int index;
        std::string data;
        std::string previousHash;
        int nonce;
        std::string hash;
        std::vector<SignedTransaction*> validTransactions;
    
    public:
        Block() = default;
        Block(int idx, const std::vector<std::string>& transactionData, const std::string& prevHash);
        void setNonce(int n);
        int getNonce() const;
        void setHash(const std::string& h);
        std::string getHash() const;
        int getIndex() const;
        std::string getData() const;
        std::string getPreviousHash() const;

};

#endif