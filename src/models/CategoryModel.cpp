/**
 * CategoryModel is responsible for managing data, including reading from file,
 * writing to file and keep track of state of data.
 */
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "giomm/error.h"
#include "giomm/file.h"
#include "json.hpp"
#include <iostream>
#include <string>
CategoryModel::CategoryModel() {
  std::cout << "🟢 [CategoryModel.cpp:13]: " << "CategoryModel Constructed"
            << std::endl;
  VaultModel vaultModel(ROOT_CONFIG_PATH);
  filePath = vaultModel.getPath() + "/" + "metadata.json";

  loadExistingData();
  if (jsonData.find("categories") == jsonData.end()) {
    jsonData["categories"] = nlohmann::json::array();
  }
}
void CategoryModel::addCategory(CategoryMetadata categoryMetadata) {

  nlohmann::json category;
  category["id"] = categoryMetadata.id;
  category["name"] = categoryMetadata.name;
  category["passwordLocked"] = categoryMetadata.passwordLocked;
  category["password"] = categoryMetadata.password;

  jsonData["categories"].push_back(category);
  for (const auto &category : jsonData["categories"]) {
    std::cout << "🟢 [CategoryModel.cpp:31]: " << "Name: "
              << category.value("name", "") << std::endl;
  }
  writeToFile();
  signalCategoryAdded.emit();
}

void CategoryModel::loadExistingData() {
  try {
    FileUtils::readJsonFromFile(filePath, jsonData);
  } catch (const std::exception &e) {
    jsonData =
        nlohmann::json::object(); // If reading fails, create new empty object.
  }
};
void CategoryModel::writeToFile() const {
  try {
    FileUtils::saveJsonToFile(filePath, jsonData);
  } catch (const std::exception &e) {
    std::cerr << "🛑[CategoryModel.cpp:49] Error : "
              << "metadata.json not found!" << filePath << std::endl;
  }
}
std::vector<CategoryMetadata> CategoryModel::getAllCategories() {
  std::vector<CategoryMetadata> categories;
  loadExistingData();
  // Check if "categories" key exists and is an array
  if (jsonData.find("categories") != jsonData.end() &&
      jsonData["categories"].is_array()) {
    // std::cout << "🟢 [CategoryModel.cpp:56]: " << "Getting all categories"
    //           << std::endl;
    for (const auto &category : jsonData["categories"]) {
      std::cout << "🟢 [CategoryModel.cpp:59]: " << "Getting all categories: "
                << category.value("id", "") << std::endl;
      CategoryMetadata metadata;
      metadata.id = category.value("id", "");
      metadata.name = category.value("name", "");
      metadata.passwordLocked = category.value("passwordLocked", false);
      metadata.password = category.value("password", "");

      categories.push_back(metadata);
    }
  } else {
    std::cerr << "🔴 [CategoryModel.cpp:73]: " << "Categories not available!!"
              << std::endl;
  }

  return categories;
}

std::vector<AssetModel>
CategoryModel::getAssetsByCategory(std::string categoryId) {
  // TODO: Add proper returns
  auto categories = this->getAllCategories();
  CategoryMetadata category;

  // Find the category with the id
  for (int i = 0; i < categories.size(); i++) {
    if (categories[i].id == categoryId) {
      category = categories[i];
      break;
    }
  }

  if (category.id.empty()) {
    // Category isn't valid, return null
  }
  VaultModel vaultModel(ROOT_CONFIG_PATH);

  // Build the filepath from category.name and vaultdata
  std::string categoryPath = vaultModel.getPath() + "/" + category.name;
  std::vector<AssetModel> assets;
  try {
    auto folder = Gio::File::create_for_path(categoryPath);
    auto enumerator =
        folder->enumerate_children("*", Gio::FileQueryInfoFlags::NONE);
  } catch (...) {
  }
  // Load all files inside category.name and build AssetModel each by each, use
  // Gio::File to read all files
}
bool CategoryModel::addAssetsToCategory(std::vector<AssetModel> assets,
                                        std::string categoryId) {
  std::cout << "🟢 [CategoryModel.cpp:118]: " << "Adding assets to category: "
            << categoryId << std::endl;
  auto categories = this->getAllCategories();
  CategoryMetadata category;

  // Find the category with the id
  for (int i = 0; i < categories.size(); i++) {
    if (categories[i].id == categoryId) {
      category = categories[i];
      break;
    }
  }

  if (category.id.empty()) {

    return false;
    // Category isn't valid, return null
  }

  std::cout << "🟢 [CategoryModel.cpp:135]: " << "Found category: "
            << category.name << std::endl;
  VaultModel vaultModel(ROOT_CONFIG_PATH);

  // Build the filepath from category.name and vaultdata
  std::string destinationPath = vaultModel.getPath() + "/" + category.name;

  auto categoryDir = Gio::File::create_for_path(destinationPath);
  // Ensure the directory exists
  // Check if the directory exists
  try {
    auto fileInfo = categoryDir->query_info();
    if (fileInfo->get_file_type() != Gio::FileType::DIRECTORY) {
      // Path exists but is not a directory
      std::cerr << "🔴 [CategoryModel.cpp:151]: " << "Not a directory"
                << std::endl;
      return false;
    }
  } catch (const Glib::Error &e) {
    // Directory does not exist or other error occurred
    if (e.code() == Gio::Error::NOT_FOUND) {
      // Directory does not exist, create it
      try {
        categoryDir->make_directory();
      } catch (const Glib::Error &createError) {
        // Handle error creating directory
        std::cerr << "Error creating directory: " << createError.what()
                  << std::endl;
        return false;
      }
    } else {
      // Other errors
      std::cerr << "Error querying directory: " << e.what() << std::endl;
      return false;
    }
  }
  // Load existing json data
  auto metadataPath = destinationPath + "/" + "metadata.json";
  FileUtils::readJsonFromFile(metadataPath, assetJsonData);
  if (!assetJsonData.contains("assets")) {
    assetJsonData["assets"] = nlohmann::json::array();
  }
  // Load existing json data
  auto metadataPath = destinationPath + "/" + "metadata.json";
  FileUtils::readJsonFromFile(metadataPath, assetJsonData);
  if (!assetJsonData.contains("assets")) {
    assetJsonData["assets"] = nlohmann::json::array();
  }
  // Process and move files
  for (auto &asset : assets) {
    try {
      // Create Gio::File instances for source and destination
      auto sourceFile = Gio::File::create_for_path(asset.filePath);
      auto destinationFile =
          Gio::File::create_for_path(destinationPath + "/" + asset.name);

      // Copy the file to the new location
      sourceFile->copy(destinationFile, Gio::File::CopyFlags::NONE);

      // Optionally, delete the source file if you want to move instead of copy
      sourceFile->remove();

      // Update asset file path
      asset.filePath = destinationPath + "/" + asset.name;
      asset.filePath = destinationPath + "/" + asset.name;

      // Asset is being moved to trash folder
      if (category.name == "trash") {
        asset.isTrashed = true;
      }
      // Get data from asset model as json
      auto assetJson = asset.toJson();

      // Add new json data to previous array
      assetJsonData["assets"].push_back(assetJson);

      // Save json to metadata.json file
      FileUtils::saveJsonToFile(metadataPath, assetJsonData);
    } catch (const Glib::Error &e) {
      // Handle error, such as file not found, permission issues, etc.
      std::cerr << "Error moving file: " << e.what() << std::endl;
      return false;
    }
  }

  // TODO: Move the file from assets[i].filepath to our filePath
  return true;
}

CategoryModel::~CategoryModel() {}