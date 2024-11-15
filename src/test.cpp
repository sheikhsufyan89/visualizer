#include <iostream>
#include <string>
#include <ctime> 
#include "classes/users/StandardUser.h"
#include "classes/transactions/Transaction.h"
#include "classes/users/User.h"
#include "classes/users/CurrentUser.h"
#include "classes/entity.h"

using namespace std;

unsigned int simpleHash(const std::string& input, time_t transactionTime) {
    unsigned int hash = 0;

    // Convert the transaction time to string
    std::string timeStr = std::to_string(transactionTime);
    std::string data = input + timeStr; // Combine the input with the transaction time

    // Iterate over each character of the combined data (input + time)
    for (char ch : data) {
        hash = hash * 31 + ch;  // Multiply by 31 and add ASCII value of the character
    }

    // Perform bitwise operations to mix the bits further
    hash ^= (hash >> 16);  // XOR with right-shifted hash
    hash *= 0x85ebca6b;    // Prime multiplier
    hash ^= (hash >> 13);  // Additional XOR and shift

    return hash;
}

// int main() {
//     // Define multiple test cases
//     struct TestCase {
//         std::string transactionData;
//         time_t transactionTime;
//     } testCases[] = {
//         {"Alice to Bob: 50", 1618330270},
//         {"Alice to Bob: 50", 1618330270},  // Duplicate to check consistency
//         {"Alice to Bob: 50", 1618330271},  // Same data, different time
//         {"Alice to Charlie: 25", 1618330270},  // Different data, same time
//         {"Bob to Alice: 100", 1618330272},  // Completely different transaction
//         {"Alice to Bob: 50", 1620000000}  // Same data, significantly different time
//     };

//     // Iterate over test cases and print the hash for each
//     for (int i = 0; i < sizeof(testCases) / sizeof(TestCase); ++i) {
//         const auto& test = testCases[i];
//         unsigned int hashValue = simpleHash(test.transactionData, test.transactionTime);
//         std::cout << "Test Case " << i + 1 << ": "
//                   << "Transaction Data: \"" << test.transactionData << "\", "
//                   << "Timestamp: " << test.transactionTime << ", "
//                   << "Hash: " << hashValue << std::endl;
//     }

//     return 0;
//}

int main(){
    StandardUser user1("alice", "password123");
    StandardUser user2("bob", "bobpassword");
    Transaction x1("bob", "sufyan", 100);



    // Transaction t1("alice", "bob", 100);
    // t1.display();
    // user1.display();
    // cout << endl;
    // cout << user1.getUsername();
    cout << User::getUser(0);
    return 0;    
}
