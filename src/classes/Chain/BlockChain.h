#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include "../blocks/Block.h"
#include "../miners/miner.h"

class BlockChain{
    private:
        std::vector<Block> chain;
        int difficulty;
        Miner miner;
    
    public:
        BlockChain(int difficulty);
        // void addBlock(const std::vector<std::string>& transactionData);
        // void mineBlock(Block &block);
        string addBlock(const std::vector<std::string>& transactionData);
        string mineBlock(Block &block);
        Block getLastBlock() const;
        bool isValidChain() const;	
        void displayChain() const;
        const std::vector<Block>& getChain() const {
            return chain;
        }
        int getDifficulty() const {
            return difficulty;
        }
        const Miner& getMiner() const {
            return miner;
        }
};

#endif