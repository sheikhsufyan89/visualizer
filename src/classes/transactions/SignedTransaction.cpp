#include "SignedTransaction.h"
#include <iostream>
#include <ctime>

using namespace std;

int SignedTransaction::counter = 0 ;

SignedTransaction::SignedTransaction(const string &id, const string &sender, const string &receiver, double amount, unsigned int hash, string signed_by, time_t timestamp)
    : Entity(id), sender(sender), receiver(receiver), amount(amount), signedBy(signed_by), hashValue(hash), timestamp(timestamp) {}

    
string SignedTransaction::genTransactionID(){
    return "STX" + to_string(++counter);
}

void SignedTransaction::display() const {
    cout << "Transaction ID: " << getId() << endl;
    cout << "  From: " << sender << endl;
    cout << "  To: " << receiver << endl;
    cout << "  Amount: " << amount << endl;
    cout << "  Timestamp: " << ctime(&timestamp);  
}

string SignedTransaction::getSignedBy(){
    return signedBy;
}

string SignedTransaction::getHashVal(){
    return to_string(hashValue);
}

string SignedTransaction::getSender(){
    return sender;
}
string SignedTransaction::getReceiver(){
    return receiver;
}
int SignedTransaction::getAmount(){
    return amount;
}

time_t SignedTransaction::getTimeStamp() const {
    return timestamp;
}
