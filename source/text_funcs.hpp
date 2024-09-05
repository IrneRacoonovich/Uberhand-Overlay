#pragma once

#include <string>
#include <utility>

std::pair<std::string, int> readTextFromFile(const std::string& filePath);

bool write_to_file(const std::string& file_path, const std::string& line);

bool remove_txt(const std::string& file_path, const std::string& pattern);
