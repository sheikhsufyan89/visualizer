#include "Transaction.h"
#include <iostream>
#include <ctime>

using namespace std;


int Transaction::counter = 0;

Transaction::Transaction(const string& sender, const string& receiver, double amount)
    : Entity(generateTransactionId()), 
      sender(sender), 
      receiver(receiver), 
      amount(amount), 
      timestamp(time(0)) {  
}

Transaction::Transaction( const string& sender, const string& receiver, double amount, const string& id)
    : Entity(id), sender(sender), receiver(receiver), amount(amount), timestamp(time(0)) {}

string Transaction::generateTransactionId() {
    return "TX" + to_string(++counter);  
}


void Transaction::display() const {
    cout << "Transaction ID: " << getId() << endl;
    cout << "  From: " << sender << endl;
    cout << "  To: " << receiver << endl;
    cout << "  Amount: " << amount << endl;
    cout << "  Timestamp: " << ctime(&timestamp);  
}

string Transaction::getSender() const {
    return sender;
}
string Transaction::getReceiver() const {
    return receiver;
}
double Transaction::getAmount() const {
    return amount;
}
time_t Transaction::getTimeStamp() const {
    return timestamp;
}