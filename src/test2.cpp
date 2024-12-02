#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <unordered_set>


std::string simpleHash(const std::string& input) {
    unsigned long hash = 0;
    for (size_t i = 0; i < input.length(); ++i) {
        hash = (hash * 31) + input[i];  
        hash = hash ^ (hash >> 16);     
        hash = hash + (hash << 8);      
        hash = hash ^ (hash >> 4);    
    }
    
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << (hash & 0xFFFFFFFF);  
    return ss.str();
}

std::string mineBlock(const std::string& data, int difficulty) {
    unsigned long nonce = 0;  
    std::string target(difficulty, '0');  
    std::string hash;
    int attempts = 0;
    std::unordered_set<std::string> seenHashes; 
    do {
        std::stringstream ss;
        ss << data.length() << nonce;  
        hash = simpleHash(ss.str());
        std::cout << "Attempt " << attempts++ << " - Nonce: " << nonce << " Hash: " << hash << std::endl;
        if (seenHashes.find(hash) != seenHashes.end()) {
            continue;  
        }

        seenHashes.insert(hash);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  

        nonce++;  

    } while (hash.substr(0, difficulty) != target);  

    std::cout << "Block mined! Nonce: " << nonce << " Hash: " << hash << std::endl;
    return hash;  
}

int main() {
    std::string data = "example data";  
    int difficulty = 2;  
    std::string minedHash = mineBlock(data, difficulty);
    std::cout << "Mined Hash: " << minedHash << std::endl;

    return 0;
}
