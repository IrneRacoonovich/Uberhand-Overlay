#pragma once

#include <istream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct PackageHeader {
    std::string version;
    std::string creator;
    std::string github;
    std::string about;
    bool enableConfigNav { false };
    bool showCurInMenu { false };
    std::string checkKipVersion;
};

PackageHeader getPackageHeaderFromIni(const std::string& filePath);

using KeyValueData = std::map<std::string, std::string>;
using IniData = std::map<std::string, KeyValueData>;

IniData parseIni(std::istream& str);

// Custom utility function for parsing an ini file
IniData getParsedDataFromIniFile(const std::string& configIniPath);

std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>> loadOptionsFromIni(const std::string& configIniPath, bool makeConfig = false);

void cleanIniFormatting(const std::string& filePath);

bool setIniFile(const std::string& fileToEdit, const std::string& desiredSection, const std::string& desiredKey, const std::string& desiredValue, const std::string& desiredNewKey);

bool setIniFileValue(const std::string& fileToEdit, const std::string& desiredSection, const std::string& desiredKey, const std::string& desiredValue);

bool setIniFileKey(const std::string& fileToEdit, const std::string& desiredSection, const std::string& desiredKey, const std::string& desiredNewKey);

bool removeIniFileKey(const std::string& fileToEdit, const std::string& desiredSection, const std::string& desiredKey);

std::string readIniValue(const std::string& filePath, const std::string& section, const std::string& key);

std::vector<std::vector<int>> parseIntIniData(std::string input, bool skipFirstItem = true);

bool isLineExistInIni(const std::string& filename, std::string& lineToFind);
