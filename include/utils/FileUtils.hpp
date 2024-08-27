#pragma once
#include "json.hpp"
#include <string>

namespace FileUtils {
// ============ Basic File Handling Operations ============
bool fileExists(const std::string &filePath);
bool writeFile(const std::string &filePath, const std::string &content);
std::string readFile(const std::string &filePath);
bool deleteFile(const std::string &filePath);
bool copyFile(const std::string &sourcePath,
              const std::string &destinationPath);
bool moveFile(const std::string &sourcePath,
              const std::string &destinationPath);

// ============ Save json data to a file ============
bool saveJsonToFile(const std::string &filePath,
                    const nlohmann::json &jsonData);

// ============ Read json data from file ============
bool readJsonFromFile(const std::string &filePath, nlohmann::json &jsonData);

}; // namespace FileUtils
