#pragma once
#include <json.hpp>
#include <string>

class VaultModel {
public:
  VaultModel() = default;
  VaultModel(const std::string &name, const std::string &path);

  // Getters and Setters
  std::string getName() const;
  void setName(const std::string &name);

  std::string getPath() const;
  void setPath(const std::string &path);

  // Serialize to JSON
  nlohmann::json toJson() const;

  // Deserialize from JSON
  static VaultModel fromJson(const nlohmann::json &j);

private:
  std::string name;
  std::string path;
};
