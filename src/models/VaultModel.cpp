#include "VaultModel.hpp"

// Constructor
VaultModel::VaultModel(const std::string &name, const std::string &path)
    : name(name), path(path) {}

// Getters and Setters
std::string VaultModel::getName() const { return name; }

void VaultModel::setName(const std::string &name) { this->name = name; }

std::string VaultModel::getPath() const { return path; }

void VaultModel::setPath(const std::string &path) { this->path = path; }

// Serialize to JSON
nlohmann::json VaultModel::toJson() const {
  nlohmann::json j;
  j["vaultName"] = name;
  j["vaultPath"] = path;
  return j;
}

// Deserialize from JSON
VaultModel VaultModel::fromJson(const nlohmann::json &j) {
  VaultModel vault;
  vault.name = j.at("vaultName").get<std::string>();
  vault.path = j.at("vaultName").get<std::string>();
  return vault;
}
