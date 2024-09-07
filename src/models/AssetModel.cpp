#include "AssetModel.hpp"
#include "constants.hpp"
#include "utils.hpp"

AssetModel::AssetModel(Glib::RefPtr<Gio::File> file) {
  auto fileInfo = file->query_info();
  id = Utils::generateId();
  name = fileInfo->get_name();
  size = Utils::formatSize(fileInfo->get_size());
  type = determineAssetType(name);
  isTrashed = false;
  createdAt = fileInfo->get_creation_date_time().format("%Y-%m-%d");
  filepath = file->get_path();
  // Constructor implementation
}

std::string AssetModel::determineAssetType(std::string &fileName) {
  size_t lastDotPos = fileName.find_last_of(".");
  if (!lastDotPos) {
    return "OTHER";
  }
  std::string extString = fileName.substr(lastDotPos + 1);
  if (Utils::isStringInArray(imageType, extString)) {
    return "IMAGE";
  } else if (Utils::isStringInArray(videoType, extString)) {
    type = "";
    return "VIDEO";
  } else if (Utils::isStringInArray(documentType, extString)) {
    return "DOCUMENTS";
  } else if (Utils::isStringInArray(codeType, extString)) {
    return "CODE";
  } else if (Utils::isStringInArray(adobeType, extString)) {
    return "ADOBE";
  } else if (Utils::isStringInArray(audioType, extString)) {
    return "AUDIO";
  } else if (Utils::isStringInArray(textType, extString)) {
    return "TEXT";
  }

  return "OTHER";
};

AssetModel::~AssetModel() {
  // Destructor implementation
}

bool AssetModel::moveAssetToCategory(
    Glib::RefPtr<Gio::File> file, std::optional<std::string> sourceCategoryId,
    std::string destinationCategoryId) {
  bool success = false;
  // Implementation to move asset to destinationCategoryId
  // If sourceCategoryId is null, handle files coming from file chooser
  return success;
}

bool AssetModel::addAsset(std::string categoryId) {
  bool success = false;
  // Implementation to add a new asset to categoryId
  return success;
}

bool AssetModel::updateName(const std::string &name) {
  // Implementation to update the asset name
  return true;
}
