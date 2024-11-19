#include <iostream>
#include <string>
#include <ctime> 
// #include "classes/users/StandardUser.h"
// #include "classes/transactions/Transaction.h"
// #include "classes/users/User.h"
// #include "classes/users/CurrentUser.h"
// #include "classes/entity.h"

using namespace std;

unsigned int simpleHash(const string& input, time_t transactionTime) {
    unsigned int hash = 0;

    string timeStr = to_string(transactionTime);
    string data = input + timeStr; 

    // Iterate over each character of the combined data (input + time)
    for (char ch : data) {
        hash = hash * 31 + ch;  // Multiply by 31 and add ASCII value of the character
    }

    hash ^= (hash >> 16);  // XOR with right-shifted hash
    hash *= 0x85ebca6b;    // Prime multiplier
    hash ^= (hash >> 13);  // Additional XOR and shift

    return hash;
}

int main(){
    // string* users = {};
    // StandardUser user1("alice", "password123");
    // StandardUser user2("bob", "bobpassword");
    // Transaction x1("bob", "sufyan", 100);
    string sender = "Sufyan";
    string receiver = "Khadeer";
    int amount  = 1000;
    string sum = sender + receiver + to_string(amount);
    time_t currentTime = time(nullptr);
    cout << simpleHash(sum, currentTime);
    

    return 0;    
}
