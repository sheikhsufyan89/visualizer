#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include "../blocks/Block.h"
#include "../miners/Miner.h"

class BlockChain{
    private:
        std::vector<Block> chain;
        int difficulty;
        Miner miner;
    
    public:
        BlockChain(int difficulty);
        void addBlock(const std::vector<std::string>& transactionData);
        void mineBlock(Block &block);
        Block getLastBlock() const;
        bool isValidChain() const;	
        void displayChain() const;
};

#endif