/**
 * CategoryModel is responsible for managing data, including reading from file,
 * writing to file and keep track of state of data.
 */
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
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

  jsonData["categories"].push_back(category);
  for (const auto &category : jsonData["categories"]) {
    std::cout << "🟢 [CategoryModel.cpp:31]: " << "Name: "
              << category.value("name", "") << std::endl;
  }
  writeToFile();
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

CategoryModel::~CategoryModel() {}