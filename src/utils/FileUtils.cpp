#include "FileUtils.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <sstream>
#include <stdexcept>
#include <sys/stat.h>

bool FileUtils::fileExists(const std::string &filePath) {
  struct stat buffer;
  return (stat(filePath.c_str(), &buffer) == 0);
}

bool FileUtils::writeFile(const std::string &filePath,
                          const std::string &content) {
  std::ofstream outFile(filePath);
  if (!outFile.is_open()) {
    return false;
  }
  outFile << content;
  outFile.close();
  return true;
}

std::string FileUtils::readFile(const std::string &filePath) {
  std::ifstream inFile(filePath);
  if (!inFile.is_open()) {
    return "";
  }
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  return buffer.str();
}

bool FileUtils::deleteFile(const std::string &filePath) {
  return (remove(filePath.c_str()) == 0);
}

bool FileUtils::copyFile(const std::string &sourcePath,
                         const std::string &destinationPath) {
  std::ifstream src(sourcePath, std::ios::binary);
  std::ofstream dest(destinationPath, std::ios::binary);

  if (!src.is_open() || !dest.is_open()) {
    return false;
  }

  dest << src.rdbuf();
  return src && dest; // check if both streams are in a good state
}

bool FileUtils::moveFile(const std::string &sourcePath,
                         const std::string &destinationPath) {
  if (std::rename(sourcePath.c_str(), destinationPath.c_str()) != 0) {
    // If renaming fails (e.g., across different file systems), fall back to
    // copy and delete
    if (!copyFile(sourcePath, destinationPath)) {
      return false;
    }
    return deleteFile(sourcePath);
  }
  return true;
}

bool FileUtils::saveJsonToFile(const std::string &filePath,
                               const nlohmann::json &jsonData) {
  std::ofstream file(filePath);
  if (file.is_open()) {
    file << jsonData.dump(4); // Pretty print with 4 spaces
    file.close();
    std::cout << "JSON data saved successfully to: " << filePath << std::endl;
    return true;
  } else {
    throw std::runtime_error("Failed to open file: " + filePath +
                             " for writing.");
  }
}
/**
 * Instead of throwing error, we just return false
 * In case file does not exist, we don't want the program to break
 * Just the second arg `jsonData` will be null.
 */
bool FileUtils::readJsonFromFile(const std::string &filePath,
                                 nlohmann::json &jsonData) {
  std::ifstream file(filePath);
  if (file.is_open()) {
    try {
      file >> jsonData;
      file.close();
      return true;
    } catch (const std::exception &e) {
      file.close();
      return false;
    }
  } else {
    return true;
  }
  return false;
}
std::vector<AssetModel> FileUtils::convertFilesToAssetModels(
    std::vector<Glib::RefPtr<Gio::File>> files) {
  std::vector<AssetModel> assetModels;
  for (const auto &file : files) {
    try {
      // The default constructor for assetmodel will automatically set the
      // necessary fields for the model
      AssetModel asset(file);

      assetModels.push_back(asset);
    } catch (const Gio::Error &e) {
      std::cerr << "Error accessing file info: " << e.what() << std::endl;
    }
  }

  return assetModels;
}