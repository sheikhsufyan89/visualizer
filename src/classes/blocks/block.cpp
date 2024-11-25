// #include "block.h"
// #include <iostream>
// #include <ctime>
// #include <sstream>

// using namespace std;

// Block::Block(int index, const std::string& previousHash)
//     : index(index), previousHash(previousHash), nonce(0), transactionCount(0) {
//     timestamp = std::time(nullptr);  // Set the current time as the block's timestamp
// }

// // Adds a transaction to the block, returns false if block transaction limit is reached
// bool Block::addTransaction(Transaction* tx) {
//     if (transactionCount < MAX_TRANSACTIONS) {
//         transactions[transactionCount++] = tx;
//         return true;
//     }
//     return false;
// }

// // Concatenate block data to create a unique string for hashing
// std::string Block::getData() const {
//     std::stringstream ss;
//     ss << index << previousHash << timestamp << nonce;
//     for (int i = 0; i < transactionCount; ++i) {
//         ss << transactions[i]->getId();  // You might want to add more transaction details here
//     }
//     return ss.str();
// }

// // Display block information and transactions
// void Block::display() const {
//     std::cout << "Block Index: " << index << "\n";
//     std::cout << "Hash: " << hash << "\n";
//     std::cout << "Previous Hash: " << previousHash << "\n";
//     std::cout << "Timestamp: " << timestamp << "\n";
//     std::cout << "Nonce: " << nonce << "\n";
//     std::cout << "Transactions:\n";
//     for (int i = 0; i < transactionCount; ++i) {
//         transactions[i]->display();  // Assuming Transaction has a display method
//     }
//     std::cout << "---------------------------------\n";
// }











// #include "block.h"
// #include <sstream>
// #include <iomanip>
// #include <openssl/sha.h>
// #include "../users/CurrentUser.h"
// #include "../transactions/SignedPool.h"

// Block::Block(int idx, std::string blockData, std::string prevHash)
//     : index(idx), data(blockData), previousHash(prevHash), nonce(0) {}

// std::string Block::computeHash() {
//     std::stringstream ss;
//     ss << index << data << previousHash << nonce;

//     unsigned char hash[SHA256_DIGEST_LENGTH];
//     SHA256((unsigned char*)ss.str().c_str(), ss.str().length(), hash);

//     std::stringstream hashString;
//     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//         hashString << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//     }
//     return hashString.str();
// }

// void Block::setNonce(int n) { nonce = n; }
// int Block::getNonce() const { return nonce; }
// void Block::setHash(const std::string& h) { hash = h; }
// std::string Block::getHash() const { return hash; }
// int Block::getIndex() const { return index; }
// std::string Block::getData() const { return data; }
// std::string Block::getPreviousHash() const { return previousHash; }








#include "block.h"
#include "../miners/miner.h"
#include <iostream>

using namespace std;

Block::Block(int idx, const std::vector<std::string>& transactionData, const std::string& prevHash)
    : index(idx), previousHash(prevHash), nonce(0){
        data = "";
        for(const auto& tx : transactionData){
            data += tx + "; " + "\n";  //after every transaction, there is a new line character
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