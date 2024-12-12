#ifndef SIGNEDTRANSACTION_H
#define SIGNEDTRANSACTION_H

#include <string>
#include <ctime>
#include "../entity.h"

class SignedTransaction : public Entity {
    private:
        string sender;
        string receiver;
        double amount;
        time_t timestamp;
        string signedBy;
        unsigned int hashValue;
  
        static int counter;
    
    public:
        SignedTransaction(const string &id, const string & sender, const string & receiver, double amount, unsigned int hash, string signed_by, time_t timestamp);

        SignedTransaction(const std::string& id, const std::string& sender, const std::string& receiver, double amount, int timestamp);

        void display() const override;

        static string genTransactionID();
        string getSignedBy();
        unsigned int getHashVal() const;
        string getSender() const ;
        string getReceiver() const ;
        time_t getTimeStamp() const;
        double getAmount() const ;
        
        
        unsigned int getHash() const {
            return static_cast<unsigned int>(hashValue);
        }
        // ~SignedTransaction();
};

#endif