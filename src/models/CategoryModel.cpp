/**
 * CategoryModel is responsible for managing data, including reading from file,
 * writing to file and keep track of state of data.
 */
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
CategoryModel::CategoryModel() {}
CategoryModel::CategoryModel(const std::string &path) : filePath(path) {

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
              << "metadata.json not found!" << std::endl;
  }
}
CategoryModel::~CategoryModel() {}