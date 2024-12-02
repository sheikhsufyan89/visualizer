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
#include "../users/User.h"

class Miner : public User {
    private:
        std::vector<ValidatedTransaction*> ValidTransactions;
        int difficulty;
    public:

        Miner() : User("", "", "Miner") {}
   
        Miner(const string& username, const string& password, int diff)
        : User(username, password, "miner"), difficulty(diff) {}

        Miner(int diff);

        unsigned int ValidationHashFunct(const SignedTransaction* stx) const;

        string ValidateAndAddTransactions(SignedPool* pool);

        void DisplayValidTransactions() const;

        void sendToValidationPool();

        static std::string computeHash(int index, const std::string& data, const std::string& previousHash, int nonce);
        string mineBlock(Block &block);

        bool meetsDifficulty(const std::string &hash);
};

#endif