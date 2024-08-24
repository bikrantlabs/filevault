#pragma once
#include "json.hpp"
#include <string>

class FileUtils {
public:
  static bool fileExists(const std::string &filePath);
  static bool writeFile(const std::string &filePath,
                        const std::string &content);
  static std::string readFile(const std::string &filePath);
  static bool deleteFile(const std::string &filePath);
  static bool copyFile(const std::string &sourcePath,
                       const std::string &destinationPath);
  static bool moveFile(const std::string &sourcePath,
                       const std::string &destinationPath);
  static bool saveJsonToFile(const std::string &filePath,
                             const nlohmann::json &jsonData);

  static bool readJsonFromFile(const std::string &filePath,
                               nlohmann::json &jsonData);
};
