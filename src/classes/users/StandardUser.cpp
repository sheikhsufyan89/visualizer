// StandardUser.cpp
#include "standardUser.h"
#include <iostream>
#include <ctime>

using namespace std;

unsigned int StandardUser::hashTransaction(const string& transactionData, time_t transactionTime) const {
    unsigned int hash = 0;
    string timeStr = to_string(transactionTime);
    string data = transactionData + timeStr;
    for (char ch : data) {
        hash = hash * 31 + ch;
    }

    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);

    return hash;
}

void StandardUser::display() const  {
    cout << "Standard User: " << username << ", Role: " << role << endl;
}
