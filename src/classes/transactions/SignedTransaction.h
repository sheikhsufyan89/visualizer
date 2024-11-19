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
        SignedTransaction(const string & sender, const string & receiver, double amount, unsigned int hash, string signed_by);

        SignedTransaction(const string &id, const string & sender, const string & receiver, double amount, unsigned int hash, string signed_by);

        void display() const override;

        static string genTransactionID();
        string getSignedBy();
        string getHashVal();
  
        // ~SignedTransaction();
};