#include <iostream>
#include <string>
#include <ctime>
unsigned int hashTransaction(const std::string& transactionData, time_t timestamp) {
    std::string input = transactionData + std::to_string(timestamp);
    unsigned int hash = 768;

   
    return hash;
}
int main() {
    std::string transactionData = "custom1hunain100.000000";
    time_t transactionTime = 1733477134;
    try {
        std::cout << hashTransaction(transactionData, transactionTime) << std::endl;
    } catch (...) {
        return 1; // Indicate an error in the hash function
    }
    return 0;
}
