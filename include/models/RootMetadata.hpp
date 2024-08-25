#pragma once
#include <json.hpp>
#include <string>

class RootMetadata {
public:
  RootMetadata() = default;

  // Getters and Setters
  std::string getName() const;
  void setName(const std::string &name);

  std::string getPath() const;
  void setPath(const std::string &path);

  // Serialize to JSON
  nlohmann::json toJson() const;

  // Deserialize from JSON
  static RootMetadata fromJson(const nlohmann::json &j);

private:
  std::string name;
  std::string path;
};
