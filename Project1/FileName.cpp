#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Function that adds the global variables
void addNumbers(int num1, int num2) {
    int result = num1 + num2;
    cout << "Addition: " << result << endl;
}

// Function that multiplies the global variables
void multiplyNumbers(int num1, int num2) {
    int result = num1 * num2;
    cout << "Multiplication: " << result << endl;
}


// Convert hex string to byte vector
std::vector<uint8_t> hexStringToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

int main() {
    std::string titleId = "00050000101d7500";
    std::string filePath = "C:\\Users\\admin\\Documents\\GitHub\\WiiUDownPatcher\\Project1\\Input\\versions.bin";

    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return 1;
    }

    // Read entire file into buffer
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // Convert titleId to bytes
    std::vector<uint8_t> titleBytes = hexStringToBytes(titleId);

    // Search for byte sequence
    auto it = std::search(buffer.begin(), buffer.end(), titleBytes.begin(), titleBytes.end());
    if (it != buffer.end()) {
        std::cout << "Title ID found at byte offset: " << std::distance(buffer.begin(), it) << std::endl;
    }
    else {
        std::cout << "Title ID not found in the file." << std::endl;
    }

    return 0;
}
