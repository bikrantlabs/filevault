#pragma once
#include <string>

class Asset {
public:
  Asset(const std::string &name, const std::string &path,
        const std::string &type);

  const std::string &getName() const;
  const std::string &getPath() const;
  const std::string &getType() const;

  void setName(const std::string &name);
  void setPath(const std::string &path);
  void setType(const std::string &type);

private:
  std::string name;
  std::string path;
  std::string type;
};
