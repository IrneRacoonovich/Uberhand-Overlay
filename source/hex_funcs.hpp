#pragma once
#include <string>
#include <vector>
#include <cstdio> // Added for FILE and fopen
#include <cstring> // Added for std::memcmp
#include <sys/stat.h> // Added for stat

// Hex-editing commands
std::string asciiToHex(const std::string& asciiStr) {
    std::string hexStr;
    hexStr.reserve(asciiStr.length() * 2); // Reserve space for the hexadecimal string

    for (char c : asciiStr) {
        unsigned char uc = static_cast<unsigned char>(c); // Convert char to unsigned char
        char hexChar[3]; // Buffer to store the hexadecimal representation (2 characters + null terminator)

        // Format the unsigned char as a hexadecimal string and append it to the result
        std::snprintf(hexChar, sizeof(hexChar), "%02X", uc);
        hexStr += hexChar;
    }

    if (hexStr.length() % 2 != 0) {
        hexStr = '0' + hexStr;
    }

    return hexStr;
}

std::string decimalToHex(const std::string& decimalStr) {
    // Convert decimal string to integer
    int decimalValue = std::stoi(decimalStr);

    // Convert decimal to hexadecimal
    std::string hexadecimal;
    while (decimalValue > 0) {
        int remainder = decimalValue % 16;
        char hexChar = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        hexadecimal += hexChar;
        decimalValue /= 16;
    }

    // Reverse the hexadecimal string
    std::reverse(hexadecimal.begin(), hexadecimal.end());

    // If the length is odd, add a trailing '0'
    if (hexadecimal.length() % 2 != 0) {
        hexadecimal = '0' + hexadecimal;
    }

    return hexadecimal;
}

std::string decimalToReversedHex(const std::string& decimalStr, int order = 2) {
    std::string hexadecimal = decimalToHex(decimalStr);

    // Reverse the hexadecimal string in groups of order
    std::string reversedHex;
    for (int i = hexadecimal.length() - order; i >= 0; i -= order) {
        reversedHex += hexadecimal.substr(i, order);
    }

    return reversedHex;
}

std::vector<u8> hexStringToBytes(const std::string& hexString) {
    if (hexString.empty()) {
        logError("hexStringToBytes: hexString is empty");
        return {};
    }

    std::vector<u8> result;
    result.reserve(hexString.length() / 2);
    for (size_t i = 0; i < hexString.length() / 2; i += 2) {
        result.push_back(std::stoi(hexString.substr(i, 2)));
    }
    return result;
}

std::vector<size_t> findDataOffsetsF(FILE* file, const std::vector<u8> binaryData) {
    std::vector<size_t> offsets;
    u8 buffer[1024];
    size_t offset = 0;
    std::size_t bytesRead = 0;
    while ((bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), file)) > 0) {
        for (std::size_t i = 0; i < (bytesRead - binaryData.size()); i++) {
            if (std::memcmp(buffer + i, binaryData.data(), binaryData.size()) == 0) {
                size_t currentOffset = offset + i;
                offsets.push_back(currentOffset);
            }
        }
        offset += bytesRead;
    }

    return offsets;
}

std::vector<size_t> findDataOffsets(const char* filePath, const std::vector<u8> binaryData) {
    struct stat fileStatus;
    if (stat(filePath, &fileStatus) != 0) {
        logError("findDataOffsets: Failed to read properties of file \"" + std::string(filePath) + "\"");
        return {};
    }

    if (!S_ISREG(fileStatus.st_mode)) {
        logError("findDataOffsets: Not a regular file: \"" + std::string(filePath) + "\"");
        return {};
    }

    FILE* file = fopen(filePath, "rb");
    if (!file) {
        logError("findDataOffsets: Failed to open the file \"" + std::string(filePath) + "\". " + std::string(strerror(errno)));
        return {};
    }

    auto result = findDataOffsetsF(file, binaryData);
    fclose(file);
    return result;
}

std::vector<u8> readHexDataAtOffset(const char* filePath, const std::vector<u8>& hexData, const size_t mainOffset, const size_t length) {

    FILE* file = fopen(filePath, "rb");
    if (!file) {
        logMessage("readHexDataAtOffset: Failed to open the file \"" + std::string(filePath) + "\"");
        return {};
    }

    auto offsets = findDataOffsetsF(file, hexData);
    if (offsets.empty()) {
        logError("readHexDataAtOffset: data not found.");
        return {};
    }

    if (fseek(file, mainOffset + offsets[0], SEEK_SET) != 0) {
        logError("readHexDataAtOffset: Error seeking to offset: " + std::string(strerror(errno)));
        fclose(file);
        return {};
    }

    std::vector<u8> result;
    result.reserve(length);

    if (fread(result.data(), sizeof(result[0]), length, file) != length) {
        if (feof(file)) {
            logError("readHexDataAtOffset: Unexpected end of file reached.");
        } else if (ferror(file)) {
            logError("readHexDataAtOffset: Error reading data from file: " + std::string(strerror(errno)));
        }
    }

    fclose(file);
    return result;
}

// Is used when mutiple read iterrations are required to reduce the number of file open/close requests
std::string readHexDataAtOffsetF(FILE* file, const std::string& custOffset, const std::string& hexData, const std::string& offsetStr, size_t length) {
    // logMessage("Entered readHexDataAtOffsetF");

    std::stringstream hexStream;
    char lowerToUpper;
    std::string result = "";
    char hexBuffer[length];
    int sum = 0;

    if (!custOffset.empty()) {
        sum = std::stoi(offsetStr) + std::stoi(custOffset); // count from "C" letter
    }
    else {
        logMessage("CUST not found.");
    }

    if (fseek(file, sum, SEEK_SET) != 0) {
        logMessage("Error seeking to offset.");
        fclose(file);
        return "";
    }

    if (fread(hexBuffer, 1, length, file) == length) {
        for (size_t i = 0; i < length; ++i) {
            hexStream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(hexBuffer[i]);
        }
    } else {
        if (feof(file)) {
            logMessage("End of file reached.");
        } else if (ferror(file)) {
            logMessage("Error reading data from file: ");
            logMessage(std::to_string(errno)); // Print the error description
        }
    }

    while (hexStream.get(lowerToUpper)) {
        result += std::toupper(lowerToUpper);
    }

    return result;
}

bool hexEditByOffset(const std::string& filePath, const size_t offset, const std::string& hexData) {
    // Open the file for reading and writing in binary mode
    FILE* file = fopen(filePath.c_str(), "rb+");
    if (!file) {
        logMessage("Failed to open the file.");
        return false;
    }

    // Move the file pointer to the specified offset
    if (fseek(file, offset, SEEK_SET) != 0) {
        logMessage("Failed to move the file pointer.");
        fclose(file);
        return false;
    }

    // Convert the hex data string to binary data
    std::vector<unsigned char> binaryData; // Changed to use unsigned char
    for (std::size_t i = 0; i < hexData.length(); i += 2) {
        std::string byteString = hexData.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16)); // Changed to use unsigned char
        binaryData.push_back(byte);
    }

    // Calculate the number of bytes to be replaced
    std::size_t bytesToReplace = binaryData.size();

    // Read the existing data from the file
    std::vector<unsigned char> existingData(bytesToReplace); // Changed to use unsigned char
    if (fread(existingData.data(), sizeof(unsigned char), bytesToReplace, file) != bytesToReplace) { // Changed to use unsigned char
        logMessage("Failed to read existing data from the file.");
        fclose(file);
        return false;
    }

    // Move the file pointer back to the offset
    if (fseek(file, offset, SEEK_SET) != 0) {
        logMessage("Failed to move the file pointer.");
        fclose(file);
        return false;
    }

    // Write the replacement binary data to the file
    if (fwrite(binaryData.data(), sizeof(unsigned char), bytesToReplace, file) != bytesToReplace) { // Changed to use unsigned char
        logMessage("Failed to write data to the file.");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
    //logMessage("Hex editing completed.");
}

// Is used when mutiple write iterrations are required to reduce the number of file open/close requests
bool hexEditByOffsetF(const std::string& filePath, std::map <size_t, std::string> data) {

    // Open the file for reading and writing in binary mode
    FILE* file = fopen(filePath.c_str(), "rb+");
    if (!file) {
        logMessage("Failed to open the file.");
        return false;
    }

    for(const auto& ov : data) {
        
        // Convert the offset string to std::streampos
        size_t offset = ov.first;
        std::string hexData = ov.second;

        // Move the file pointer to the specified offset
        if (fseek(file, offset, SEEK_SET) != 0) {
            logMessage("Failed to move the file pointer.");
            fclose(file);
            return false;
        }

        // Convert the hex data string to binary data
        std::vector<unsigned char> binaryData; // Changed to use unsigned char
        for (std::size_t i = 0; i < hexData.length(); i += 2) {
            std::string byteString = hexData.substr(i, 2);
            unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16)); // Changed to use unsigned char
            binaryData.push_back(byte);
        }

        // Calculate the number of bytes to be replaced
        std::size_t bytesToReplace = binaryData.size();

        // Read the existing data from the file
        std::vector<unsigned char> existingData(bytesToReplace); // Changed to use unsigned char
        if (fread(existingData.data(), sizeof(unsigned char), bytesToReplace, file) != bytesToReplace) { // Changed to use unsigned char
            logMessage("Failed to read existing data from the file.");
            fclose(file);
            return false;
        }

        // Move the file pointer back to the offset
        if (fseek(file, offset, SEEK_SET) != 0) {
            logMessage("Failed to move the file pointer.");
            fclose(file);
            return false;
        }

        // Write the replacement binary data to the file
        if (fwrite(binaryData.data(), sizeof(unsigned char), bytesToReplace, file) != bytesToReplace) { // Changed to use unsigned char
            logMessage("Failed to write data to the file.");
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
    //logMessage("Hex editing completed.");
}

bool hexEditFindReplace(const std::string& filePath, const std::string& hexDataToReplace, const std::string& hexDataReplacement, const size_t occurrence = 0) {
    auto offsets = findDataOffsets(filePath.c_str(), hexStringToBytes(hexDataToReplace));
    if (offsets.empty()) {
        logMessage("Hex data to replace not found.");
        return false;
    }
    if (occurrence == 0) { // Replace all occurrences
        for (const auto& offset : offsets) {
            hexEditByOffset(filePath, offset, hexDataReplacement);
        }
    }
    else { // Replace one occurence
        if (occurrence > offsets.size()) {
            logMessage("Invalid occurrence/index specified.");
            return false;
        }
        auto offset = offsets[occurrence - 1];
        hexEditByOffset(filePath, offset, hexDataReplacement);

    }
    return true;
}

bool hexEditCustOffset(const std::string& filePath, const size_t offset, const std::string& hexDataReplacement) {
    auto custOffset = findDataOffsets(filePath.c_str(), { 'C','U','S','T' });
    if (custOffset.empty()) {
        logError("CUST not found.");
        return false;
    }
    int sum = offset + custOffset[0]; // count from "C" letter
    hexEditByOffset(filePath, sum, hexDataReplacement);

    return true;
}

int reversedHexToInt(const std::string& hex_str) {
    std::string reversedHex;

    for (int i = hex_str.length() - 2; i >= 0; i -= 2) {
        reversedHex += hex_str.substr(i, 2);
    }
    std::istringstream iss(reversedHex);
    iss >> std::hex;

    int result;
    iss >> result;

    return result;
}