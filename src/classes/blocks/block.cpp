#include "block.h"
#include "../miners/miner.h"
#include <iostream>

using namespace std;

Block::Block(int idx, const std::vector<std::string>& transactionData, const std::string& prevHash)
    : index(idx), previousHash(prevHash), nonce(0){
        data = "";
        for(const auto& tx : transactionData){
            data += tx + "; " + "\n";  
        }
        hash = Miner::computeHash(index, data, previousHash, nonce);
}

void Block::setNonce(int n) { nonce = n; }
int Block::getNonce() const { return nonce;}
void Block::setHash(const std::string& h) { hash = h; }
std::string Block::getHash() const { return hash; }
int Block::getIndex() const { return index; }
std::string Block::getData() const { return data; }
std::string Block::getPreviousHash() const { return previousHash; }