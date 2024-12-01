// #ifndef MINER_H
// #define MINER_H

// #include "../blocks/block.h"

// class Miner {
// private:
//     int difficulty;

// public:
//     Miner(int diff);
//     void mineBlock(Block& block);
// };

// #endif











#ifndef MINER_H
#define MINER_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "../transactions/SignedPool.h"
#include "../transactions/SignedTransaction.h"
#include "../transactions/ValidationPool.h"
#include "../blocks/block.h"

class Miner {
    private:
        // std::vector<SignedTransaction*> ValidTransactions;
        std::vector<ValidatedTransaction*> ValidTransactions;
        int difficulty;


    public:
        Miner() = default;

        Miner(int diff);

        unsigned int ValidationHashFunct(const SignedTransaction* stx) const;

        void ValidateAndAddTransactions(SignedPool& pool);

        void DisplayValidTransactions() const;

        void sendToValidationPool();

        static std::string computeHash(int index, const std::string& data, const std::string& previousHash, int nonce);

        void mineBlock(Block &block);

        bool meetsDifficulty(const std::string &hash);
};

#endif