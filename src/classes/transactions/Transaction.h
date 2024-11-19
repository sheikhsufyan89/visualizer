#ifndef TRANSACTION_H
#define TRANSACTION_H

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
    
Transaction(const string& sender, const string& receiver, double amount, const string& id);
    

    ~Transaction() {}
    static string generateTransactionId();
    string getSender() const;
    string getReceiver() const;
    double getAmount() const;
    time_t getTimeStamp() const;
};

#endif 
