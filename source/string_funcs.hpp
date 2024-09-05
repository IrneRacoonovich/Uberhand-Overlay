#pragma once

#include <string>

constexpr const char* WhitespaceCharacters = " \t\n\r\f\v";

// In-place trimming of whitespace characters for rvalue strings
std::string trim(std::string&& str);

// In-place trimming of whitespace characters
void trimInPlace(std::string& str);

std::string removeQuotes(const std::string& str);

std::string replaceMultipleSlashes(const std::string& input);

std::string removeLeadingSlash(const std::string& pathPattern);

std::string removeEndingSlash(const std::string& pathPattern);

std::string preprocessPath(const std::string& path);

std::string preprocessUrl(const std::string& path);

std::string dropExtension(const std::string& filename);

std::string getExtension(const std::string& filename);

bool startsWith(const std::string& str, const std::string& prefix);

// Path functions
bool isDirectory(const std::string& path);

bool isFileOrDirectory(const std::string& path);

std::string getSubstringAfterLastSlash(const std::string& str);
