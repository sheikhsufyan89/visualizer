#include "BlockChain.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor to initialize the blockchain with a difficulty level
BlockChain::BlockChain(int diff) : miner(diff), difficulty(diff) {
    // Create the genesis block (the first block in the chain)
    vector<string> genesisTransactions = {"Genesis Block"};
    Block genesisBlock(0, genesisTransactions, "0");  // No previous hash for the genesis block
    mineBlock(genesisBlock);  // Mine the genesis block
    chain.push_back(genesisBlock);  // Add the genesis block to the chain
}

// Method to add a new block to the blockchain
void BlockChain::addBlock(const vector<string>& transactionData) {
    string previousHash = getLastBlock().getHash();  // Get the hash of the last block
    Block newBlock(chain.size(), transactionData, previousHash);  // Create a new block
    mineBlock(newBlock);  // Mine the block
    chain.push_back(newBlock);  // Add the mined block to the chain
}

// Method to mine a block
void BlockChain::mineBlock(Block &block) {
    miner.mineBlock(block);  // Use the miner to mine the block
}

// Method to get the last block in the chain
Block BlockChain::getLastBlock() const {
    if (chain.empty()) {
        cout << "Block chain is empty!" << endl;
    }
    return chain.back();
}

// Method to check if the blockchain is valid
bool BlockChain::isValidChain() const {
    // Iterate through the chain and check if each block's previous hash matches
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];

        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;  // Invalid chain if the previous hash does not match
        }
        // Validate the block's hash against its content
        if (currentBlock.getHash() != miner.computeHash(currentBlock.getIndex(), currentBlock.getData(), currentBlock.getPreviousHash(), currentBlock.getNonce())) {
            return false;  // Invalid block if its hash does not match the computed hash
        }
    }
    return true;  // The blockchain is valid if all blocks are correctly linked and hashed
}

// Method to display the entire blockchain
void BlockChain::displayChain() const {
    for (const Block& block : chain) {
        cout << "Block Index: " << block.getIndex() << endl;
        cout << "Data: " << block.getData() << endl;
        cout << "Hash: " << block.getHash() << endl;
        cout << "Previous Hash: " << block.getPreviousHash() << endl;
        cout << "------------------------------" << endl;
    }
}
