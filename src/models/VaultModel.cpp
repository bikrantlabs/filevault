#include "VaultModel.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include <iostream>

// Constructor
VaultModel::VaultModel(const std::string &name, const std::string &path)
    : name(name), path(path) {}
VaultModel::VaultModel(const std::string &filePath) { loadFromFile(filePath); }

// Getters and Setters
std::string VaultModel::getName() const { return name; }
std::string VaultModel::getActiveScreen() const { return activeScreen; }
void VaultModel::setName(const std::string &name) { this->name = name; }

std::string VaultModel::getPath() const { return path; }

void VaultModel::setPath(const std::string &path) { this->path = path; }
void VaultModel::setActiveScreen(const std::string &activeScreen) {
  this->activeScreen = activeScreen;
}
// Serialize to JSON
nlohmann::json VaultModel::toJson() const {
  nlohmann::json j;
  j["vaultName"] = name;
  j["vaultPath"] = path;
  j["activeScreen"] = activeScreen;
  return j;
}

void VaultModel::loadFromFile(const std::string &filePath) {
  // Check if filePath exists

  nlohmann::json jsonData;
  try {
    FileUtils::readJsonFromFile(filePath, jsonData);
    *this = fromJson(jsonData); // Deserialize into this object
  } catch (const std::exception &e) {
    std::cerr << "🛑[VaultModel.cpp:32] Error : " << e.what() << std::endl;
  }
}

// Deserialize from JSON
VaultModel VaultModel::fromJson(const nlohmann::json &j) {
  VaultModel vault;
  vault.name = j.at("vaultName").get<std::string>();
  vault.path = j.at("vaultPath").get<std::string>();
  vault.activeScreen = j.at("activeScreen").get<std::string>();

  // Optionally if vault.path exists but actually directory doesn't
  if (!FolderUtils::directoryExists(vault.path)) {
    // create the dir:
    FolderUtils::createFolder(vault.path);
  }
  return vault;
}
VaultModel::~VaultModel() {}