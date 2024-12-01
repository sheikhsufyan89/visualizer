#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>

// Function to write user-provided code to a file
void writeCodeToFile(const std::string& code, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << code;
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing.\n";
        exit(1);
    }
}

// Function to compile and execute the code, redirecting output to a file
int compileAndExecute(const std::string& cppFile, const std::string& executable) {
    // Step 1: Compile the code
    std::string command = "g++ " + cppFile + " -o " + executable;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Compilation failed.\n";
        exit(1);
    }

    // Step 2: Execute the compiled program and redirect its output to a file
    command = executable + ".exe > output.txt";  // Redirect output to a file
    result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Execution failed.\n";
        exit(1);
    }

    return 0;
}

// Function to read the output from the file
std::string readOutputFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open output file for reading.\n";
        exit(1);
    }

    std::string output;
    std::string line;
    while (std::getline(file, line)) {
        output += line + "\n";
    }

    file.close();
    return output;
}

// Function to check if the user-provided code contains the correct function signature and return type
bool checkFunctionSignature(const std::string& code) {
    // Check for the correct return type and function signature
    if (code.find("std::string hashFunction(const std::string& input)") != std::string::npos &&
        code.find("std::string") != std::string::npos) {
        return true;
    }
    return false;
}

int main() {
    // User-provided code with the correct function signature
    std::string userCode = R"(
#include <iostream>
#include <string>

// Correct function signature as requested
std::string hashFunction(const std::string& input) {
    std::string hash;
    for (char c : input) {
        hash += std::to_string(static_cast<int>(c) * 2); // Example hash logic
    }
    return hash;
}

int main() {
    std::string input = "Hello, world!";
    std::string hashValue = hashFunction(input);
    std::cout << hashValue << std::endl;
    return 0;
}
)";

    // Check if the function signature and return type are correct
    if (!checkFunctionSignature(userCode)) {
        std::cerr << "Error: Function signature or return type is incorrect.\n";
        std::cerr << "Expected: std::string hashFunction(const std::string& input)\n";
        exit(1);
    } else {
        std::cout << "Function signature and return type are correct.\n";
    }

    // Define the filenames
    std::string cppFile = "hash_function.cpp";
    std::string executable = "user_program";
    std::string outputFile = "output.txt";

    // Write, compile, and execute the user code
    writeCodeToFile(userCode, cppFile);
    compileAndExecute(cppFile, executable);

    // Read the output from the file
    std::string output = readOutputFromFile(outputFile);

    // Print the captured hash value
    std::cout << "Captured hash: " << output << std::endl;

    return 0;
}
