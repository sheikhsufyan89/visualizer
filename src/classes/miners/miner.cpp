// #include "miner.h"
// #include <iostream>
// #include <chrono>
// #include <thread>

// Miner::Miner(int diff) : difficulty(diff) {}

// void Miner::mineBlock(Block& block) {
//     std::string target(difficulty, '0');
//     int nonce = 0;
//     std::string hash;

//     do {
//         block.setNonce(++nonce);
//         hash = block.computeHash();
//         std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         std::cout << "Attempting nonce: " << nonce << " | Hash: " << hash << "\n";
//     } while (hash.substr(0, difficulty) != target);

//     block.setHash(hash);
//     std::cout << "Block mined! Nonce: " << nonce << " | Hash: " << hash << "\n";
// }







#include "miner.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Miner::Miner(int diff) : difficulty(diff) {}


unsigned int Miner::ValidationHashFunct(const SignedTransaction* stx) const {
    unsigned int hash  = 0;

    string transaction_data = stx->getSender() + stx->getReceiver() + to_string(stx->getAmount());
    string timeStr = to_string(stx->getTimeStamp());
    string data = transaction_data + timeStr;

    for (char ch : data) {
        hash = hash * 31 + ch;
    }

    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);

    cout << "Hash of the transaction " << stx->getId() << ": " << hash << std::endl;
    return hash;
}

void Miner::ValidateAndAddTransactions(SignedPool& pool) {
        std::vector<SignedTransaction*> validTransactionsToProcess;

    // Loop through each transaction in the SignedPool
    for (int i = 0; i < pool.getPendingCount(); ++i) {
        SignedTransaction* stx = pool.getTransaction(i);  // Use accessor method to get the transaction

        // Check if the transaction is valid
        if (stx != nullptr) {
            // Compute the hash of the transaction using the ValidationHashFunct
            unsigned int computedHash = ValidationHashFunct(stx);

            // Check if the computed hash matches the stored hashValue in the SignedTransaction
            if (computedHash == stx->getHashVal()) {
                cout << "Transaction " << stx->getId() << " added with hash: " << computedHash << endl;
                cout << endl;

                validTransactionsToProcess.push_back(stx);  // Collect valid transactions
            } else {
                cout << "Transaction " << stx->getId() << " discarded due to hash mismatch." << endl;
                cout << "Hash received/entered through constructor call was: " << stx->getHashVal() << endl;
                cout << endl;
            }
        }
    }

    // Now process and delete the valid transactions
    for (SignedTransaction* stx : validTransactionsToProcess) {
        ValidatedTransaction* validatedTx = new ValidatedTransaction(stx->getId(), stx->getSender(), stx->getReceiver(), stx->getAmount(), stx->getTimeStamp());
        ValidTransactions.push_back(validatedTx);  // Store validated transaction
        // Add valid transaction to block
        pool.processTransaction(stx->getId());  // Process and remove the transaction from the pool
    }

    sendToValidationPool();
}

void Miner::DisplayValidTransactions() const {
    cout << endl << "Valid Transactions in this block:" << endl;
    for (const auto& tx : ValidTransactions) {
        tx->display();  // Assuming SignedTransaction has a display method
        cout << endl;
    }
}




void Miner::sendToValidationPool() {
    // Get the singleton instance of ValidationPool
    ValidationPool* validatedPool = ValidationPool::getInstance("MyValidationPool");

    // Iterate over the valid transactions stored in ValidTransactions
    for (ValidatedTransaction* vtx : ValidTransactions) {
        if (validatedPool->addValidatedTransaction(vtx)) {
            cout << "Transaction " << vtx->getId() << " added to ValidationPool." << endl;
        } else {
            cout << "Transaction " << vtx->getId() << " could not be added to ValidationPool (pool full)." << endl;
        }
    }

}


std::string Miner::computeHash(int index, const std::string& data, const std::string& previousHash, int nonce) {
    std::stringstream ss;
    ss << index << data << previousHash << nonce;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)ss.str().c_str(), ss.str().length(), hash);

    std::stringstream hashString;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hashString << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return hashString.str();
}


// // simple one not showing nonce values in the terminal
// void Miner::mineBlock(Block &block) {
//     std::string currentHash;

//     do {
//         block.setNonce(block.getNonce() + 1);

//         currentHash = computeHash(block.getIndex(), block.getData(), block.getPreviousHash(), block.getNonce());

//     } while (!meetsDifficulty(currentHash));

//     block.setHash(currentHash);
//     cout << "Block mined with hash: " << currentHash << endl;
// }



void Miner::mineBlock(Block &block) {
    std::string currentHash;

    int maxAttempts = 1000000;  // Or any reasonable limit
    int attempts = 0;

    do {
        block.setNonce(block.getNonce() + 1);
        currentHash = computeHash(block.getIndex(), block.getData(), block.getPreviousHash(), block.getNonce());

        cout << "Trying nonce: " << block.getNonce() << " -> Hash: " << currentHash << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        attempts++;
    } while (!meetsDifficulty(currentHash) && attempts < maxAttempts);

    if (attempts >= maxAttempts) {
        cout << "Mining attempt limit reached. Difficulty may be too high." << endl;
    } else {
        block.setHash(currentHash);  // Set the valid hash to the block
        cout << endl;
        cout << "Block mined with hash: " << currentHash << endl;
        cout << endl;
    }

}






bool Miner::meetsDifficulty(const std::string &hash) {
    return hash.substr(0, difficulty) == std::string(difficulty, '0');  //Difficulty is the number of leading zeros
}
