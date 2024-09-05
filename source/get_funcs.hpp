#pragma once

#include <switch/result.h>

#include <string>
#include <tuple>
#include <vector>

// Overlay Module settings
constexpr Result ResultSuccess = MAKERESULT(0, 0);

std::tuple<Result, std::string, std::string> getOverlayInfo(const std::string& filePath);

// Function to read the content of a file
std::string getFileContents(const std::string& filePath);

std::string getFileNameFromURL(const std::string& url);

std::string getDestinationPath(const std::string& destinationDir, const std::string& fileName);

std::string getValueFromLine(const std::string& line);

std::string getNameFromPath(const std::string& path);

std::string getParentDirFromPath(const std::string& path);

std::string getParentDirNameFromPath(const std::string& path);

std::string getNameWithoutPrefix(std::string Name);

std::vector<std::string> getSubdirectories(const std::string& directoryPath);

std::vector<std::string> getFilesListFromDirectory(const std::string& directoryPath);

// get files list for file patterns and folders list for folder patterns
std::vector<std::string> getFilesListByWildcard(const std::string& pathPattern);

std::vector<std::string> getFilesListByWildcards(const std::string& pathPattern);

std::string replacePlaceholder(const std::string& input, const std::string& placeholder, const std::string& replacement);

std::string replaceJsonSourcePlaceholder(const std::string& placeholder, const std::string& jsonPath, std::string searchString = "{json_data(");

std::vector<std::vector<std::string>> getModifyCommands(const std::vector<std::vector<std::string>>& commands, const std::string& file, bool toggle = false, bool on = true, bool usingJsonSource = false);
