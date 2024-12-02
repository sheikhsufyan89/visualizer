#include "miner.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream> 

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

    return hash;
}

std::string Miner::ValidateAndAddTransactions(SignedPool* pool) {
    if (pool == nullptr) {
        return "Error: Null pointer passed for SignedPool.";
    }

    std::vector<std::string> validTransactionIDs;
    std::vector<std::string> invalidTransactionIDs;

    for (int i = 0; i < pool->getPendingCount(); ++i) {
        SignedTransaction* stx = pool->getTransaction(i);
        if (stx != nullptr) {
            unsigned int computedHash = ValidationHashFunct(stx);
            if (computedHash == stx->getHashVal()) {
                validTransactionIDs.push_back(stx->getId());
                ValidatedTransaction* validatedTx = new ValidatedTransaction(
                    stx->getId(), stx->getSender(), stx->getReceiver(), stx->getAmount(), stx->getTimeStamp()
                );
                ValidTransactions.push_back(validatedTx); 
                pool->processTransaction(stx->getId());  
            } else {
                invalidTransactionIDs.push_back(stx->getId()); 
            }
        }
    }
    sendToValidationPool();
    std::stringstream summary;
    summary << "Validation Summary:\n";
    summary << "Valid Transactions (" << validTransactionIDs.size() << "): ";
    for (const std::string& id : validTransactionIDs) {
        summary << id << " ";
    }
    summary << "\nInvalid Transactions (" << invalidTransactionIDs.size() << "): ";
    for (const std::string& id : invalidTransactionIDs) {
        summary << id << " ";
    }
    summary << "\n";

    return summary.str(); 
}


void Miner::DisplayValidTransactions() const {
    cout << endl << "Valid Transactions in this block:" << endl;
    for (const auto& tx : ValidTransactions) {
        tx->display();  
        cout << endl;
    }
}

void Miner::sendToValidationPool() {
    ValidationPool* validatedPool = ValidationPool::getInstance("MyValidationPool");
    for (ValidatedTransaction* vtx : ValidTransactions) {
        if (validatedPool->addValidatedTransaction(vtx)) {
            // cout << "Transaction " << vtx->getId() << " added to ValidationPool." << endl;
        } else {
            // cout << "Transaction " << vtx->getId() << " could not be added to ValidationPool (pool full)." << endl;
        }
    }

}

std::string simpleHash(const std::string& input) {
    unsigned long hash = 0;
    for (size_t i = 0; i < input.length(); ++i) {
        hash = (hash * 31) + input[i];  
        hash = hash ^ (hash >> 16);    
        hash = hash + (hash << 8);     
        hash = hash ^ (hash >> 4);     
    }
    
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << (hash & 0xFFFFFFFF);  
    return ss.str();
}

std::string Miner::computeHash(int index, const std::string& data, const std::string& previousHash, int nonce) {
    std::stringstream ss;
    ss << index << data << previousHash << nonce;
    return simpleHash(ss.str());  
}

std::string Miner::mineBlock(Block &block) {
    std::string currentHash;
    std::stringstream logStream; 

    int maxAttempts = 1000000;  
    int attempts = 0;

    do {
        block.setNonce(block.getNonce() + 1);
        currentHash = computeHash(block.getIndex(), block.getData(), block.getPreviousHash(), block.getNonce());
        logStream << "Trying nonce: " << block.getNonce() << " -> Hash: " << currentHash << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        attempts++;
    } while (!meetsDifficulty(currentHash) && attempts < maxAttempts);

    if (attempts >= maxAttempts) {
        logStream << "Mining attempt limit reached. Difficulty may be too high.\n";
    } else {
        block.setHash(currentHash);  
        logStream << "\n";
        logStream << "Block mined with hash: " << currentHash << "\n";
        logStream << "\n";
    }

    return logStream.str();
}

bool Miner::meetsDifficulty(const std::string &hash) {
    return hash.substr(0, difficulty) == std::string(difficulty, '0');  
}
