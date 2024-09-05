#pragma once

#include <string>
#include <vector>

// Function to create a directory if it doesn't exist
void createSingleDirectory(const std::string& directoryPath);

// Function to create a directory (including nested directories) if it doesn't exist
void createDirectory(const std::string& directoryPath);

// Function to create a text file with the specified content
void createTextFile(const std::string& filePath, const std::string& content);

void removeEntryFromList(const std::string& entry, std::vector<std::string>& fileList);

// Delete functions
bool deleteFileOrDirectory(const std::string& pathToDelete);

bool deleteFileOrDirectoryByPattern(const std::string& pathPattern);

bool mirrorDeleteFiles(const std::string& sourcePath, const std::string& targetPath = "sdmc:/");

// Move functions
bool moveFileOrDirectory(const std::string& sourcePath, const std::string& destinationPath);

bool moveFilesOrDirectoriesByPattern(const std::string& sourcePathPattern, const std::string& destinationPath);

// Copy functions
bool copySingleFile(const std::string& fromFile, const std::string& toFile);

bool copyFileOrDirectory(const std::string& fromFileOrDirectory, const std::string& toFileOrDirectory);

bool copyFileOrDirectoryByPattern(const std::string& sourcePathPattern, const std::string& toDirectory);

bool mirrorCopyFiles(const std::string& sourcePath, const std::string& targetPath = "sdmc:/");

bool generateBackup();
