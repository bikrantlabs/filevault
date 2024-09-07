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
#include "giomm/file.h"
#include "glibmm/refptr.h"
#include <optional>
#include <string>
#include <vector>
enum AssetTypes { IMAGE, TEXT, CODE, ADOBE, DOCUMENTS, VIDEO, AUDIO, OTHER };

class AssetModel {
public:
  AssetModel(Glib::RefPtr<Gio::File> file);
  ~AssetModel();

  /**
   * Move the received files from source to destination
   * If sourceCategoryId is null, files are coming from filechooser
   */
  bool moveAssetToCategory(Glib::RefPtr<Gio::File> file,
                           std::optional<std::string> sourceCategroyId,
                           std::string destinationCategoryId);
  std::string determineAssetType(std::string &str);
  bool addAsset(std::string categoryId);

  bool updateName(const std::string &name);

  std::string id;
  std::string name;
  std::string description;
  std::string size;
  bool isTrashed;
  std::string type;
  std::string filepath;
  std::string createdAt;
  std::vector<std::string> tags;

  // Private constructors
};
// auto asset = AssetModel(File);
//  asset.