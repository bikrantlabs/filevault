
#pragma once
#include "giomm/file.h"
#include "glibmm/refptr.h"
#include "json.hpp"
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
  nlohmann::json toJson();

  std::string id;
  std::string name;
  std::string description;
  std::string size;
  bool isTrashed;
  std::string type;
  std::string filePath;
  std::string createdAt;
  std::vector<std::string> tags;
  nlohmann::json assetJsonData;
  // Private constructors
};
// auto asset = AssetModel(File);
//  asset.