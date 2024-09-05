#pragma once

#include "tesla.hpp"

#include <string>

SafeJson loadJsonFromUrl(const std::string& url);

bool downloadFile(const std::string& url, const std::string& toDestination, tsl::elm::ListItem* listItem = nullptr, int totalCommands = -1, int curProgress = -1);

bool unzipFile(const std::string& zipFilePath, const std::string& toDestination, tsl::elm::ListItem* listItem = nullptr, int totalCommands = -1, int curProgress = -1);
