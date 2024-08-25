#pragma once
#include <json.hpp>
#include <string>

class VaultModel {
public:
  VaultModel() = default;

  // Constructor to write name, and path to the file
  VaultModel(const std::string &name, const std::string &path);

  // Constructor to set name and path from the file, this constructor will use
  // loadFromFile() within.
  VaultModel(const std::string &filePath);
  ~VaultModel();
  // Getters and Setters
  std::string getName() const;
  void setName(const std::string &name);
  void loadFromFile(const std::string &filePath);

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
