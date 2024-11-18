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
      timestamp(time(0)) {  // Initialize timestamp with the current time
}

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

string Transaction::getsender() const {
    return sender;
}
string Transaction::getReceiver() const {
    return receiver;
}
// double Transaction::getAmount() const {
//     return amount;
// }