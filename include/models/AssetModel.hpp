// #pragma once
// #include <string>

// class Asset {
// public:
//   Asset(const std::string &name, const std::string &path,
//         const std::string &type);

//   const std::string &getName() const;
//   const std::string &getPath() const;
//   const std::string &getType() const;

//   void setName(const std::string &name);
//   void setPath(const std::string &path);
//   void setType(const std::string &type);

// private:
//   std::string name;
//   std::string path;
//   std::string type;
// };
#pragma once
#include <string>
#include <vector>
enum AssetTypes { IMAGE, TEXT, CODE, ADOBE, DOCUMENTS, VIDEO, AUDIO, OTHER };

typedef struct Asset {
  std::string id;
  std::string name;
  std::string description;
  int size;
  bool isTrashed;
  AssetTypes type;
  std::string createdAt;
  std::vector<std::string> tags;
} Asset;

class AssetModel {
public:
  std::vector<Asset> getAssetByCategory(std::string categoryId);
  Asset getAsset(std::string assetId);
  bool addAsset(std::string categoryId);

  bool updateName(const std::string &name);
};
