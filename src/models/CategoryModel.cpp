/**
 * CategoryModel is responsible for managing data, including reading from file,
 * writing to file and keep track of state of data.
 */
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "giomm/error.h"
#include "giomm/file.h"
#include "json.hpp"
#include <iostream>
#include <string>
CategoryModel::CategoryModel() {
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
  category["iconPath"] = categoryMetadata.iconPath;

  jsonData["categories"].push_back(category);
  writeToFile();
  signalCategoryAdded.emit();
}
void CategoryModel::updateRootPath(std::string &path) {
  filePath = path + "/" + "metadata.json";
  loadExistingData();
}
void CategoryModel::loadExistingData() {
  std::cout << "🟢 [CategoryModel.cpp:43]: " << "Loading existing data from "
            << filePath << std::endl;
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
      CategoryMetadata metadata;
      metadata.id = category.value("id", "");
      metadata.name = category.value("name", "");
      metadata.passwordLocked = category.value("passwordLocked", false);
      metadata.password = category.value("password", "");
      metadata.iconPath = category.value("iconPath", "");
      categories.push_back(metadata);
    }
  } else {
    std::cerr << "🔴 [CategoryModel.cpp:73]: " << "Categories not available!!"
              << std::endl;
  }

  return categories;
}
std::vector<CategoryMetadata> CategoryModel::getDefaultCategories() {
  std::vector<CategoryMetadata> defaultCategories;
  loadExistingData();
  // Check if "defaultCategories" key exists and is an array
  if (jsonData.find("defaultCategories") != jsonData.end() &&
      jsonData["defaultCategories"].is_array()) {
    // std::cout << "🟢 [CategoryModel.cpp:56]: " << "Getting all
    // defaultCategories"
    //           << std::endl;
    for (const auto &category : jsonData["defaultCategories"]) {
      CategoryMetadata metadata;
      metadata.id = category.value("id", "");
      metadata.name = category.value("name", "");
      metadata.passwordLocked = category.value("passwordLocked", false);
      metadata.password = category.value("password", "");
      metadata.iconPath = category.value("iconPath", "");

      defaultCategories.push_back(metadata);
    }
  } else {
    std::cerr << "🔴 [CategoryModel.cpp:73]: "
              << "defaultCategories not available!!" << std::endl;
  }

  return defaultCategories;
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
  // We don't want to return Gio::File, instead we want to do:
  // asset = AssetModel(file) and the constructor will create everything for us
  // Also, setup counter for no of files read.
}
bool CategoryModel::addAssetsToCategory(std::vector<AssetModel> assets,
                                        std::string categoryId) {
  auto categories = this->getAllCategories();
  auto defaultCategories = this->getDefaultCategories();
  categories.insert(categories.end(), defaultCategories.begin(),
                    defaultCategories.end());
  CategoryMetadata category;

  // Find the category with the id
  for (int i = 0; i < categories.size(); i++) {
    std::cout << "🟢 [CategoryModel.cpp:151]: " << "Categories: "
              << categories[i].name << std::endl;
    if (categories[i].id == categoryId) {
      category = categories[i];
      break;
    }
  }

  if (category.id.empty()) {

    return false;
    // Category isn't valid, return null
  }

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
  // Process and move files
  for (auto &asset : assets) {
    try {
      // Create Gio::File instances for source and destination
      auto sourceFile = Gio::File::create_for_path(asset.filePath);
      auto destinationFile =
          Gio::File::create_for_path(destinationPath + "/" + asset.name);
      std::cout << "🟢 [CategoryModel.cpp:210]: "
                << "Adding asset to destination:" << destinationPath
                << std::endl;
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
void CategoryModel::createDefaultCategories(std::string &path) {

  std::vector<CategoryMetadata> defaultCategories = {
      {"all", "All files", "../assets/box.png", "", false},
      {"uncategorized", "Uncategorized", "../assets/file-question.png", "",
       false},
      {"untagged", "Untagged", "../assets/square-x.png", "", false},
      {"trash", "Trash", "../assets/trash-2.png", "", false},
  };
  nlohmann::json categoriesJson;
  categoriesJson["defaultCategories"] = nlohmann::json::array();
  for (const auto &category : defaultCategories) {

    FolderUtils::createFolder(path + "/" + category.name);

    nlohmann::json categoryJson = {{"id", category.id},
                                   {"name", category.name},
                                   {"iconPath", category.iconPath},
                                   {"password", ""},
                                   {"passwordLocked", false}};

    categoriesJson["defaultCategories"].push_back(categoryJson);
  }
  FileUtils::saveJsonToFile(path + "/" + "metadata.json", categoriesJson);
  loadExistingData();
  std::cout << "🟢 [CategoryModel.cpp:248]: "
            << "Saved default files metadata.json" << std::endl;
}
CategoryModel::~CategoryModel() {}