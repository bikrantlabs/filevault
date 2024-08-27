/**
 * CategoryModel is responsible for managing data, including reading from file,
 * writing to file and keep track of state of data.
 */
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "json.hpp"
#include <string>
CategoryModel::CategoryModel(const std::string &path) : filePath(path) {
  // TODO: Save json to file
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
  if (!FileUtils::readJsonFromFile(filePath, jsonData)) {
    jsonData =
        nlohmann::json::object(); // If reading fails, create new empty object.
  }
};
void CategoryModel::writeToFile() const {
  FileUtils::saveJsonToFile(filePath, jsonData);
}
CategoryModel::~CategoryModel() {}