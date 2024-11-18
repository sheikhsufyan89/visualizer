// #ifndef TRANSACTION_H
// #define TRANSACTION_H

#include <string>
#include <ctime>
#include "../entity.h"  

using namespace std;

class Transaction : public Entity {
private:
    string sender;
    string receiver;
    double amount;
    time_t timestamp;

    static int counter;

public:
   
    Transaction(const string& sender, const string& receiver, double amount);
    void display() const override;
    
    ~Transaction() {}

    // Static method to get the next transaction ID
    static string generateTransactionId();
    string getsender() const;
    string getReceiver() const;
    // double amount();
};

// #endif 
