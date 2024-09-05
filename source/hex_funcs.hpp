#pragma once

#include <cstdio>
#include <map>
#include <string>
#include <vector>

// Hex-editing commands
std::string asciiToHex(const std::string& asciiStr);

std::string decimalToHex(const std::string& decimalStr);

std::string decimalToReversedHex(const std::string& decimalStr, int order = 2);

std::vector<size_t> findHexDataOffsetsF(FILE* const file, const std::string& hexData);

std::vector<size_t> findHexDataOffsets(const std::string& filePath, const std::string& hexData);

std::string readHexDataAtOffsetF(FILE* const file, const size_t offset, size_t length);

std::string readHexDataAtOffset(const std::string& filePath, const std::string& hexData, const size_t offsetFromData, size_t length);

FILE* openFile(const std::string& filePath);

long findCustOffset(FILE* const file);

std::string readHexDataAtOffset(FILE* const file, const std::string& hexData, const size_t offsetFromData, size_t length, int custOffset = -1);

std::string readHexDataAtOffsetF(FILE* const file, const size_t offset, const size_t length);

bool hexEditByOffset(const std::string& filePath, const size_t offset, const std::string& hexData);

// Is used when mutiple write iterrations are required to reduce the number of file open/close requests
bool hexEditByOffsetF(const std::string& filePath, const std::map<std::string, std::string>& data);

bool hexEditFindReplace(const std::string& filePath, const std::string& hexDataToReplace, const std::string& hexDataReplacement, const std::string& occurrence = "0");

bool hexEditCustOffset(const std::string& filePath, const size_t offsetFromCust, const std::string& hexDataReplacement);

int reversedHexToInt(const std::string& hex_str);

std::string findCurrentKip(const std::string& jsonPath, const std::string& offset, FILE* kipFile, int custOffset);
