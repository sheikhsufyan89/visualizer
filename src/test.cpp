// #include <iostream>
// #include <string>
// #include <ctime> 
// // #include "classes/users/StandardUser.h"
// // #include "classes/transactions/Transaction.h"
// // #include "classes/users/User.h"
// // #include "classes/users/CurrentUser.h"
// // #include "classes/entity.h"

// using namespace std;

// unsigned int simpleHash(const string& input, time_t transactionTime) {
//     unsigned int hash = 0;

//     string timeStr = to_string(transactionTime);
//     string data = input + timeStr; 

//     // Iterate over each character of the combined data (input + time)
//     for (char ch : data) {
//         hash = hash * 31 + ch;  // Multiply by 31 and add ASCII value of the character
//     }

//     hash ^= (hash >> 16);  // XOR with right-shifted hash
//     hash *= 0x85ebca6b;    // Prime multiplier
//     hash ^= (hash >> 13);  // Additional XOR and shift

//     return hash;
// }

// int main(){
//     // string* users = {};
//     // StandardUser user1("alice", "password123");
//     // StandardUser user2("bob", "bobpassword");
//     // Transaction x1("bob", "sufyan", 100);
//     string sender = "Sufyan";
//     string receiver = "Khadeer";
//     int amount  = 1000;
//     string sum = sender + receiver + to_string(amount);
//     time_t currentTime = time(nullptr);
//     cout << simpleHash(sum, currentTime);
    

//     return 0;    
// }





// // Run command: g++ -Isrc/classes/blocks -Isrc/classes/miners -I"C:/Strawberry/c/include" src/test.cpp src/classes/miners/miner.cpp src/classes/blocks/block.cpp -L"C:/Strawberry/c/lib" -lssl -lcrypto -o test
// // Run command: ./test
// #include "classes/blocks/block.h"
// #include "classes/miners/miner.h"
// #include <vector>
// #include <iostream>
// #include <thread>
// #include <openssl/sha.h>

// int main() {
//     std::vector<std::string> v;
//     int difficulty = 1; // Adjust difficulty for testing
//     Miner miner(difficulty);

//     std::cout << "Starting blockchain simulation...\n";

//     // Create the Genesis Block
//     Block genesisBlock(0, "Genesis Block", "0");
//     std::cout << "Mining Genesis Block...\n";
//     miner.mineBlock(genesisBlock);
//     std::cout << "Genesis Block Hash: " << genesisBlock.getHash() << "\n\n";
//     v.push_back(genesisBlock.getHash());
//     std::this_thread::sleep_for(std::chrono::seconds(2));

//     // Create the second block
//     Block secondBlock(1, "Transaction Data: Alice pays Bob 10 BTC", genesisBlock.getHash());
//     std::cout << "Mining Block 1...\n";
//     miner.mineBlock(secondBlock);
//     std::cout << "Block 1 Hash: " << secondBlock.getHash() << "\n\n";
//     v.push_back(secondBlock.getHash());
//     std::this_thread::sleep_for(std::chrono::seconds(2));

//     std::cout << "\nDisplaying the hashes in the vector now:\n";
//     for (const auto& hash : v) {
//         std::cout << hash << "\n";
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//     }

//     for (size_t i = 1; i < v.size(); i++) {
//         if (v[i] != v[i - 1]) {
//             std::cout << "Safe! The values in the vector are not the same.\n";
//         } else {
//             std::cout << "The values " << v[i] << " and " << v[i - 1] << " are the same!\n";
//         }
//     }

//     std::cout << "Blockchain simulation complete!\n";

//     return 0;
// }









// /*
// commands to run the code
// #include <iostream>g++ -o test_block src/test.cpp src/classes/blocks/block.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/SignedTransaction.cpp -std=c++11
// ./test_block
// */
// #include "classes/blocks/block.h"

// int main() {
//     // Create a SignedPool using the singleton instance
//     SignedPool* pool = SignedPool::getInstance("MySignedPool");

//     // Add signed transactions
//     pool->addSTransaction(new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000));  //incorrect
//     pool->addSTransaction(new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003));  //correct
//     pool->addSTransaction(new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006)); //incorrect
//     pool->addSTransaction(new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001)); //correct



//     // Create a Block and validate the transactions
//     Block block;
//     block.validateAndAddTransactions(*pool);  // Pass the pool as a reference

//     // Display valid transactions in the block
//     block.displayValidTransactions();

//     return 0;
// }













// /*
//     commands to run the code
//     g++ -std=c++17 -I src/classes/transactions -o test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidationPool.cpp src/classes/miners/Miner.cpp
//     ./test
// */

// #include <iostream>
// #include "../src/classes/transactions/SignedTransaction.h" // Ensure you include your transaction class headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"

// using namespace std;

// int main() {
//     // Create a pool of signed transactions
//     SignedPool& pool = *SignedPool::getInstance("MySignedPool");  // Get instance as reference

//     // Add some sample transactions to the pool
//     pool.addSTransaction(new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000));  
//     pool.addSTransaction(new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003));  
//     pool.addSTransaction(new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006)); 
//     pool.addSTransaction(new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001));

//     // Display all pending transactions in the SignedPool
//     cout << "Initial Signed Pool Transactions:" << endl;
//     pool.display();

//     // Create a Miner object with a specific difficulty level (example: 2)
//     Miner miner(2);

//     // Validate and add transactions
//     cout << "\nMiner validating transactions..." << endl;
//     miner.ValidateAndAddTransactions(pool);  // Pass as reference

//     // Display validated transactions in the Miner
//     miner.DisplayValidTransactions();

//     // Display the remaining pending transactions in the SignedPool
//     cout << "\nRemaining Signed Pool Transactions:" << endl;
//     pool.display();

//     // Display validated transactions in the ValidationPool
//     ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");
//     cout << "\nTransactions in the Validation Pool:" << endl;
//     validationPool->display();

//     // Test removing a transaction from the ValidationPool
//     cout << "\nAttempting to delete transaction STX1 from the ValidationPool..." << endl;
//     if (validationPool->deleteValidatedTransaction("STX1")) {
//         cout << "Transaction STX1 successfully removed from the ValidationPool." << endl;
//     } else {
//         cout << "Transaction STX1 not found in the ValidationPool." << endl;
//     }

//     cout << "\nAttempting to delete transaction STX12 from the ValidationPool..." << endl;
//     if (validationPool->deleteValidatedTransaction("STX12")) {
//         cout << "Transaction STX12 successfully removed from the ValidationPool." << endl;
//     } else {
//         cout << "Transaction STX12 not found in the ValidationPool." << endl;
//     }

//     // Display the updated ValidationPool
//     cout << "\nUpdated Validation Pool:" << endl;
//     validationPool->display();

//     // Add a big gap between the printed outputs
//     cout << "\n\n\n\n\n\n\n"; // Multiple newlines to create a large gap

//     // Finally, print the transactions in the ValidationPool
//     cout << "\nTransactions in the Validation Pool after gap:" << endl;
//     validationPool->display();

//     return 0;
// }








/*
    commands to run this code
    g++ -std=c++17 -I src/classes/transactions -I src/classes/miners -I src/classes/blocks -o test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidationPool.cpp src/classes/miners/Miner.cpp src/classes/blocks/Block.cpp -lcrypto
    ./test
*/
// #include <iostream>
// #include "../src/classes/transactions/SignedTransaction.h"  // Include transaction headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"
// #include "../src/classes/blocks/Block.h"  // Include your Block class header
// #include <vector>
// #include <ctime>

// using namespace std;

// int main() {
//     // Step 1: Create a SignedPool instance and add Signed Transactions
//     SignedPool& signedPool = *SignedPool::getInstance("MySignedPool");

//     // Add sample signed transactions
//     signedPool.addSTransaction(new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000));  
//     signedPool.addSTransaction(new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003));  
//     signedPool.addSTransaction(new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006)); 
//     signedPool.addSTransaction(new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001));


//     cout << "Signed Transactions in SignedPool:" << endl;
//     signedPool.display();

//     // Step 2: Use a Miner to validate transactions
//     Miner miner(2); // Difficulty level set to 2
//     cout << "\nValidating transactions with Miner..." << endl;
//     miner.ValidateAndAddTransactions(signedPool); // Validate transactions and move to ValidationPool

//     // Step 3: Display Validated Transactions in ValidationPool
//     ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");
//     cout << "\nValidated Transactions in ValidationPool:" << endl;
//     validationPool->display();

//     // Step 4: Collect validated transactions to create a block
//     vector<string> transactionData;
//     for (int i = 0; i < 100; ++i) { // Assuming up to 100 transactions
//         ValidatedTransaction* transaction = validationPool->getTransaction(i);
//         if (transaction != nullptr) {
//             // Format transaction as string for block data
//             string txData = "ID: " + transaction->getId() +
//                             ", Sender: " + transaction->getSender() +
//                             ", Receiver: " + transaction->getReceiver() +
//                             ", Amount: " + to_string(transaction->getAmount()) +
//                             ", Timestamp: " + to_string(transaction->getTimestamp());
//             transactionData.push_back(txData);
//         }
//     }

//     // Step 5: Create a block with the validated transaction data
//     Block newBlock(1, transactionData, "0"); // Example block with index 1 and previous hash "0"

//     // Step 6: Display block information
//     cout << "\nBlock created:" << endl;
//     cout << "Index: " << newBlock.getIndex() << endl;
//     cout << "Data: " << newBlock.getData() << endl;
//     cout << "Hash: " << newBlock.getHash() << endl;
//     cout << "Previous Hash: " << newBlock.getPreviousHash() << endl;

//     return 0;
// }










/*
    commands to run this code
    g++ -std=c++17 -I src/classes/transactions -I src/classes/miners -I src/classes/blocks -o test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidationPool.cpp src/classes/miners/Miner.cpp src/classes/blocks/Block.cpp -lcrypto
    ./test

    This code is the one in which one block is created and mined
*/
// #include <iostream>
// #include "../src/classes/transactions/SignedTransaction.h"  // Include transaction headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"
// #include "../src/classes/blocks/Block.h"  // Include your Block class header
// #include <vector>
// #include <ctime>

// using namespace std;

// int main() {
//     // Step 1: Create a SignedPool instance and add Signed Transactions
//     SignedPool& signedPool = *SignedPool::getInstance("MySignedPool");

//     // Add sample signed transactions
//     signedPool.addSTransaction(new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000));  
//     signedPool.addSTransaction(new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003));  
//     signedPool.addSTransaction(new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006)); 
//     signedPool.addSTransaction(new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001));

//     cout << "Signed Transactions in SignedPool:" << endl;
//     signedPool.display();

//     // Step 2: Use a Miner to validate transactions
//     Miner miner(2); // Difficulty level set to 2
//     cout << "\nValidating transactions with Miner..." << endl;
//     miner.ValidateAndAddTransactions(signedPool); // Validate transactions and move to ValidationPool

//     // Step 3: Display Validated Transactions in ValidationPool
//     ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");
//     cout << "\nValidated Transactions in ValidationPool:" << endl;
//     validationPool->display();

//     // Step 4: Collect validated transactions to create a block
//     vector<string> transactionData;
//     for (int i = 0; i < 100; ++i) { // Assuming up to 100 transactions
//         ValidatedTransaction* transaction = validationPool->getTransaction(i);
//         if (transaction != nullptr) {
//             // Format transaction as string for block data
//             string txData = "ID: " + transaction->getId() +
//                             ", Sender: " + transaction->getSender() +
//                             ", Receiver: " + transaction->getReceiver() +
//                             ", Amount: " + to_string(transaction->getAmount()) +
//                             ", Timestamp: " + to_string(transaction->getTimestamp());
//             transactionData.push_back(txData);
//         }
//     }

//     // Step 5: Create a block with the validated transaction data
//     Block newBlock(1, transactionData, "0"); // Example block with index 1 and previous hash "0"

//     // Step 6: Mine the block using the Miner
//     cout << "\nMining the block..." << endl;
//     miner.mineBlock(newBlock);  // This will mine the block and set its hash

//     // Step 7: Display block information
//     cout << "\nBlock created:" << endl;
//     cout << "Index: " << newBlock.getIndex() << endl;
//     cout << "Data: " << newBlock.getData() << endl;
//     cout << "Hash: " << newBlock.getHash() << endl;
//     cout << "Previous Hash: " << newBlock.getPreviousHash() << endl;

//     return 0;
// }








/*
    commands to run this code
    g++ -std=c++17 -I src/classes/transactions -I src/classes/miners -I src/classes/blocks -o test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidationPool.cpp src/classes/miners/Miner.cpp src/classes/blocks/Block.cpp -lcrypto
    ./test

    This code is the one in which two seperate blocks are being created and mined. How I am testing this is that the transactions being processed are the same 4 but are being done two times.
    Meaning that for block1, the valid transactions are STX9 and STX7. For block2, the valid transactions are also STX9 and STX7. The only difference is that the previous hash for both the blocks is different
    and the new hash is calculated on the basis of index, transaction data, and the previous block's hash. Hence the difference in the hash values. So no two hash values will be the same.
*/

// #include <iostream>
// #include "../src/classes/transactions/SignedTransaction.h"  // Include transaction headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"
// #include "../src/classes/blocks/Block.h"  // Include your Block class header
// #include <vector>
// #include <ctime>

// using namespace std;

// // Function to create and mine a block
// string createAndMineBlock(Miner& miner, ValidationPool* validationPool, int blockIndex, const string& previousHash) {
//     // Collect validated transactions to create a block
//     vector<string> transactionData;
//     for (int i = 0; i < 100; ++i) { // Assuming up to 100 transactions
//         ValidatedTransaction* transaction = validationPool->getTransaction(i);
//         if (transaction != nullptr) {
//             // Format transaction as string for block data
//             string txData = "ID: " + transaction->getId() +
//                             ", Sender: " + transaction->getSender() +
//                             ", Receiver: " + transaction->getReceiver() +
//                             ", Amount: " + to_string(transaction->getAmount()) +
//                             ", Timestamp: " + to_string(transaction->getTimestamp());
//             transactionData.push_back(txData);
//         }
//     }

//     // Create a new block with the validated transaction data and previous hash
//     Block newBlock(blockIndex, transactionData, previousHash);

//     // Mine the block using the Miner
//     cout << "\nMining the block " << blockIndex << "..." << endl;
//     miner.mineBlock(newBlock);  // This will mine the block and set its hash

//     // Display block information
//     cout << "\nBlock " << blockIndex << " created:" << endl;
//     cout << "Index: " << newBlock.getIndex() << endl;
//     cout << "Data: " << newBlock.getData() << endl;
//     cout << "Hash: " << newBlock.getHash() << endl;
//     cout << "Previous Hash: " << newBlock.getPreviousHash() << endl;

//     // Return the current block's hash to be used as the previousHash for the next block
//     return newBlock.getHash();
// }

// int main() {
//     // Create a SignedPool instance and add Signed Transactions
//     SignedPool& signedPool = *SignedPool::getInstance("MySignedPool");

//     // Add sample signed transactions
//     signedPool.addSTransaction(new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000));  
//     signedPool.addSTransaction(new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003));  
//     signedPool.addSTransaction(new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006)); 
//     signedPool.addSTransaction(new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001));

//     cout << "Signed Transactions in SignedPool:" << endl;
//     signedPool.display();

//     // Use a Miner to validate transactions
//     Miner miner(2); // Difficulty level set to 2
//     cout << "\nValidating transactions with Miner..." << endl;
//     miner.ValidateAndAddTransactions(signedPool); // Validate transactions and move to ValidationPool

//     // Display Validated Transactions in ValidationPool
//     ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");
//     cout << "\nValidated Transactions in ValidationPool:" << endl;
//     validationPool->display();

//     // Create and mine the first block
//     string firstBlockHash = createAndMineBlock(miner, validationPool, 1, "0"); // Block 1 with previous hash "0"

//     // Create and mine the second block using the actual hash of the first block
//     createAndMineBlock(miner, validationPool, 2, firstBlockHash); // Block 2 with previous hash set to the actual hash of Block 1

//     return 0;
// }











// /*
//     commands to run this code
//     g++ -std=c++17 -I src/classes/transactions -I src/classes/miners -I src/classes/blocks -o test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidationPool.cpp src/classes/miners/Miner.cpp src/classes/blocks/Block.cpp -lcrypto
//     ./test

//     This code is the one in which two seperate blocks are being created and mined but it is starting from the SignedTransaction class unlike the previous one being started from SignePool class
//     How I am testing this is that the transactions being processed are the same 4 but are being done two times.
//     Meaning that for block1, the valid transactions are STX9 and STX7. For block2, the valid transactions are also STX9 and STX7. The only difference is that the previous hash for both the blocks is different
//     and the new hash is calculated on the basis of index, transaction data, and the previous block's hash. Hence the difference in the hash values. So no two hash values will ever be the same.
// */

// #include <iostream>
// #include "../src/classes/transactions/SignedTransaction.h"  // Include transaction headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"
// #include "../src/classes/blocks/Block.h"  // Include your Block class header
// #include <vector>
// #include <ctime>
// #include <thread>
// #include <chrono>

// using namespace std;

// string createAndMineBlock(Miner& miner, ValidationPool* validationPool, int blockIndex, const string& previousHash) {
//     // Collect validated transactions to create a block
//     vector<string> transactionData;
//     for (int i = 0; i < 100; ++i) { // Assuming up to 100 transactions
//         ValidatedTransaction* transaction = validationPool->getTransaction(i);
//         if (transaction != nullptr) {
//             // Format transaction as string for block data
//             string txData = "ID: " + transaction->getId() +
//                             ", Sender: " + transaction->getSender() +
//                             ", Receiver: " + transaction->getReceiver() +
//                             ", Amount: " + to_string(transaction->getAmount()) +
//                             ", Timestamp: " + to_string(transaction->getTimestamp());
//             transactionData.push_back(txData);
//         }
//     }

//     // Create a new block with the validated transaction data and previous hash
//     Block newBlock(blockIndex, transactionData, previousHash);

//     // Mine the block using the Miner
//     cout << "\nMining the block " << blockIndex << "..." << endl;
//     miner.mineBlock(newBlock);  // This will mine the block and set its hash

//     // Display block information
//     cout << "\nBlock " << blockIndex << " created:" << endl;
//     cout << "Index: " << newBlock.getIndex() << endl;
//     cout << "Data: " << newBlock.getData() << endl;
//     cout << "Hash: " << newBlock.getHash() << endl;
//     cout << "Previous Hash: " << newBlock.getPreviousHash() << endl;
//     cout << endl;
//     this_thread::sleep_for(chrono::seconds(2));     // Sleep for 2 seconds 

//     // Return the current block's hash to be used as the previousHash for the next block
//     return newBlock.getHash();
// }

// int main() {
//     // Create Signed Transactions manually
//     cout << "Creating Signed Transactions..." << endl;

//     // Creating individual SignedTransaction objects
//     SignedTransaction* tx1 = new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000);   // 1700000000 value is the time stamp in unicode
//     SignedTransaction* tx2 = new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003);
//     SignedTransaction* tx3 = new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006);
//     SignedTransaction* tx4 = new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001);

//     // Add them directly to the SignedPool (using the pool singleton pattern)
//     SignedPool& signedPool = *SignedPool::getInstance("MySignedPool");
//     signedPool.addSTransaction(tx1);
//     signedPool.addSTransaction(tx2);
//     signedPool.addSTransaction(tx3);
//     signedPool.addSTransaction(tx4);

//     // Display the Signed Transactions in the pool
//     cout << "Signed Transactions in SignedPool:" << endl;
//     signedPool.display();

//     // Validate and Add Signed Transactions to ValidationPool
//     cout << "\nValidating transactions with Miner..." << endl;
//     Miner miner(2); // Difficulty level set to 2
//     miner.ValidateAndAddTransactions(signedPool); // Validate transactions and move to ValidationPool

//     // Display Validated Transactions in ValidationPool
//     ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");
//     cout << "\nValidated Transactions in ValidationPool:" << endl;
//     validationPool->display();

//     // Create and mine the first block
//     string firstBlockHash = createAndMineBlock(miner, validationPool, 1, "0"); // Block 1 with previous hash "0"

//     // Create and mine the second block using the actual hash of the first block
//     createAndMineBlock(miner, validationPool, 2, firstBlockHash); // Block 2 with previous hash set to the actual hash of Block 1

//     return 0;
// }















// #include "../src/classes/transactions/SignedTransaction.h"  // Include transaction headers
// #include "../src/classes/transactions/ValidatedTransaction.h"
// #include "../src/classes/transactions/SignedPool.h"
// #include "../src/classes/transactions/ValidationPool.h"
// #include "../src/classes/miners/Miner.h"
// #include "../src/classes/blocks/Block.h"  // Include your Block class header
// #include "../src/classes/Chain/BlockChain.h"
// #include <iostream>
// #include <vector>
// #include <thread>
// #include <chrono>

// using namespace std;

// int main() {
//     cout << "Program started" << endl;
//     // Step 1: Create some signed transactions
//     vector<SignedTransaction*> transactions;

//     // Create some example transactions
//     SignedTransaction* tx1 = new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000);   // 1700000000 value is the time stamp in unicode
//     SignedTransaction* tx2 = new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003);
//     SignedTransaction* tx3 = new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006);
//     SignedTransaction* tx4 = new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001);

//     transactions.push_back(tx1);
//     transactions.push_back(tx2);
//     transactions.push_back(tx3);
//     transactions.push_back(tx4);

//     // Step 2: Add transactions to the SignedPool (assumes a pool exists to hold signed transactions)
//     SignedPool pool;
//     for (auto& tx : transactions) {
//         pool.addSTransaction(tx);
//     }

//     // Step 3: Create a Miner instance and use it to validate and process transactions
//     Miner miner(4);  // Difficulty of 4 for mining

//     // Validate and add valid transactions to the pool
//     miner.ValidateAndAddTransactions(pool);

//     // Step 4: Create the Blockchain with a difficulty level of 4
//     BlockChain blockchain(4);

//     // Step 5: Create blocks and add them to the blockchain using transactions from the pool
//     vector<string> txData1 = {"TX1: Alice -> Bob: 50", "TX2: Bob -> Charlie: 30"};
//     blockchain.addBlock(txData1);

//     vector<string> txData2 = {"TX3: Charlie -> Dave: 10", "TX4: Dave -> Alice: 20"};
//     blockchain.addBlock(txData2);

//     // Step 6: Display the blockchain
//     blockchain.displayChain();

//     // Step 7: Validate the blockchain
//     if (blockchain.isValidChain()) {
//         cout << "Blockchain is valid!" << endl;
//     } else {
//         cout << "Blockchain is invalid!" << endl;
//     }

//     // Cleanup allocated memory
//     for (auto& tx : transactions) {
//         delete tx;
//     }

//     return 0;
// }






// #include "classes/transactions/SignedTransaction.h"
// #include "classes/transactions/SignedPool.h"
// #include "classes/transactions/ValidatedTransaction.h"
// #include "classes/transactions/ValidationPool.h"
// #include "classes/blocks/Block.h"
// #include "classes/Chain/BlockChain.h"
// #include "classes/miners/Miner.h"
// #include <iostream>
// #include <ctime>
// #include <vector>

// using namespace std;

// int main() {
//     cout << "Program started" << endl;

//     // Step 1: Create a pool of signed transactions
//     SignedPool* pool = SignedPool::getInstance("MySignedPool");

//     vector<SignedTransaction*> transactions = {
//         new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000),   // 1700000000 value is the time stamp in unicode
//         new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003),
//         new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006),
//         new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001),
//     };

//     for (auto& tx : transactions) {
//         pool->addSTransaction(tx);  // Add transactions to the pool
//     }

//     cout << "Transactions added to the pool" << endl;

//     // Step 3: Create a Miner instance
//     Miner miner(1);  // Difficulty of 1 for mining

//     // Step 4: Validate and add valid transactions from the pool to a ValidationPool (or directly to blockchain if no ValidationPool)
//     miner.ValidateAndAddTransactions(*pool);

//     cout << "Transactions validated and added by miner" << endl;

//     // Step 5: Create a Blockchain instance
//     BlockChain blockchain(1);  // Difficulty level for the blockchain mining

//     // Step 6: Create blocks with transaction data and add them to the blockchain
//     vector<string> txData1 = {"TX1: Alice -> Bob: 50", "TX2: Bob -> Charlie: 30"};
//     blockchain.addBlock(txData1);

//     vector<string> txData2 = {"TX3: Charlie -> Dave: 10", "TX4: Dave -> Alice: 20"};
//     blockchain.addBlock(txData2);

//     cout << "Blocks added to the blockchain" << endl;

//     // Step 7: Display the blockchain
//     blockchain.displayChain();

//     cout << "Blockchain displayed" << endl;

//     // Clean up dynamically allocated SignedTransaction objects
//     for (auto& tx : transactions) {
//         delete tx;
//     }

//     cout << "Program ended" << endl;

//     return 0;
// }











/*
    Command to run this code
    g++ -std=c++17 -I src/classes/transactions -I src/classes/miners -I src/classes/blocks -I src/classes/Chain -o blockchain_test src/test.cpp src/classes/transactions/SignedTransaction.cpp src/classes/transactions/SignedPool.cpp src/classes/transactions/ValidatedTransaction.cpp src/classes/transactions/ValidationPool.cpp src/classes/blocks/Block.cpp src/classes/Chain/BlockChain.cpp src/classes/miners/Miner.cpp -lcrypto
    ./blockchain_test
*/

#include "classes/transactions/SignedTransaction.h"
#include "classes/transactions/SignedPool.h"
#include "classes/transactions/ValidatedTransaction.h"
#include "classes/transactions/ValidationPool.h"
#include "classes/blocks/Block.h"
#include "classes/Chain/BlockChain.h"
#include "classes/miners/Miner.h"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int main() {
    cout << "Program started" << endl;

    SignedPool* pool = SignedPool::getInstance("MySignedPool");

    vector<SignedTransaction*> transactions = {
        new SignedTransaction("STX1", "Bob", "Charlie", 50.0, 67890, "Miner2", 1700000000),   // 1700000000 value is the time stamp in unicode
        new SignedTransaction("STX9", "Dave", "Eve", 100.0, 2925523637, "Miner9", 1700000003),
        new SignedTransaction("STX12", "Frank", "Grace", 75.0, 667788990, "Miner12", 1700000006),
        new SignedTransaction("STX7", "Bob", "Charlie", 75.0, 1767195885, "Miner7", 1700000001),
        new SignedTransaction("STX20", "Alice", "Dave", 120.0, 803728866, "Miner8", 1700000012),
    };

    for (auto& tx : transactions) {
        pool->addSTransaction(tx);  // Adding transactions to the pool
    }

    cout << "Transactions added to the pool" << endl;

    Miner miner(0);  // Difficulty of 1 for mining

    ValidationPool* validationPool = ValidationPool::getInstance("MyValidationPool");

    miner.ValidateAndAddTransactions(*pool);

    cout << "Transactions validated and added by miner" << endl;
    cout << endl;

    BlockChain blockchain(2);  // Difficulty level for the blockchain mining. For some reason, difficulty of blockchain is effecting the minig process and the difficulty of mining constructor is not.

    vector<string> txData1;
    for (int i = 0; i < validationPool->getValidatedCount(); ++i) {
        ValidatedTransaction* tx = validationPool->getTransaction(i);
        if (tx != nullptr) {
            txData1.push_back(tx->getId() + ": " + tx->getSender() + " -> " + tx->getReceiver() + ": " + to_string(tx->getAmount()));
        }
    }
    blockchain.addBlock(txData1);

    cout << "Blocks added to the blockchain" << endl;

    blockchain.displayChain();

    cout << "Blockchain displayed" << endl;

    for (auto& tx : transactions) {
        delete tx;
    }

    cout << "Program ended" << endl;

    return 0;
}