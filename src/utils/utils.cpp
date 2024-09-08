#include "utils.hpp"
#include "FileUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>

std::string Utils::getGeneratedIdsFilePath() {
  VaultModel vault(ROOT_CONFIG_PATH);
  std::filesystem::path filePath =
      std::filesystem::path(vault.getPath()) / "generated_ids.json";
  std::ifstream file(filePath);
  if (!file.good())
    // Create empty json and return path
    FileUtils::saveJsonToFile(filePath, nlohmann::json::object());
  return filePath;
}
bool Utils::isIdInFile(const std::string &id) {
  std::ifstream file(Utils::getGeneratedIdsFilePath());
  if (!file) {
    return false; // File doesn't exist, so ID is not in file
  }

  nlohmann::json jsonData;
  file >> jsonData;
  file.close();

  if (!jsonData.contains("generated_ids")) {
    return false; // No "generated_ids" array in JSON
  }

  for (const auto &existingId : jsonData["generated_ids"]) {
    if (existingId.get<std::string>() == id) {
      return true; // ID found in file
    }
  }

  return false; // ID not found in file
}
void Utils::saveIdToFile(const std::string &id) {
  nlohmann::json jsonData;
  std::string filePath = Utils::getGeneratedIdsFilePath();
  std::ifstream file(filePath);
  if (file) {
    file >> jsonData;
    file.close();
  }
  std::cout << "ℹ️[utils.cpp:58] FilePath : " << filePath << std::endl;

  if (!jsonData.contains("generated_ids")) {
    jsonData["generated_ids"] = nlohmann::json::array();
  }

  jsonData["generated_ids"].push_back(id);

  std::ofstream outFile(filePath);
  outFile << jsonData.dump(4); // Pretty print with 4 spaces
  std::cout << "ℹ️[utils.cpp:58] Info : " << "Saved Id to File" << std::endl;
  outFile.close();
}
std::string Utils::generateId() {
  const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);

  std::string id;
  bool unique = false;

  while (!unique) {
    id.clear();
    for (int i = 0; i < 6; ++i) {
      id += characters[distribution(generator)];
    }

    // Check if ID is unique
    if (!Utils::isIdInFile(id)) {
      unique = true;
      Utils::saveIdToFile(id);
    }
  }

  return id;
}

bool Utils::isStringInArray(const std::vector<std::string> &vec,
                            const std::string &value) {
  return std::find(vec.begin(), vec.end(), value) != vec.end();
}
std::string Utils::formatSize(long long bytes) {
  if (bytes < 0) {
    return "Invalid size";
  }

  const double KB = 1000.0;
  const double MB = KB * 1000.0;
  const double GB = MB * 1000.0;

  std::ostringstream oss;
  double size;

  if (bytes >= GB) {
    size = bytes / GB;
    oss << std::fixed << std::setprecision(2) << size << "GB";
  } else if (bytes >= MB) {
    size = bytes / MB;
    oss << std::fixed << std::setprecision(2) << size << "MB";
  } else if (bytes >= KB) {
    size = bytes / KB;
    oss << std::fixed << std::setprecision(2) << size << "KB";
  } else {
    size = bytes;
    oss << size << "B";
  }

  // Correct rounding by using round function
  double roundedSize = std::round(size * 100) / 100;
  std::ostringstream finalOss;
  finalOss << std::fixed << std::setprecision(2) << roundedSize;

  // Construct final string
  return finalOss.str() +
         (bytes >= GB ? "GB"
                      : (bytes >= MB ? "MB" : (bytes >= KB ? "KB" : "B")));
}
// std::string Utils::extractActiveScreenId