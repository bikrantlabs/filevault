#include "CategoryController.hpp"
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <filesystem>
#include <iostream>

CategoryController::CategoryController() {}

void CategoryController::onAddCategory(const std::string &categoryName,
                                       const std::string &password) {
  try {
    CategoryModel &categoryModel = CategoryModel::getInstance();

    VaultModel vault(ROOT_CONFIG_PATH);
    FolderUtils::createCategoryFolder(categoryName);

    // Create category metadata.json

    // Add created category data to root metadata.json
    std::string uniqueId = Utils::generateId();
    CategoryMetadata categoryMetadata = {uniqueId, categoryName, true,
                                         "password1234"};
    categoryModel.addCategory(categoryMetadata);

    // Create an empty metadatsa.json insdie that  category
    std::filesystem::path _metadata =
        std::filesystem::path(vault.getPath()) / categoryName / "metadata.json";
    FileUtils::saveJsonToFile(_metadata, nlohmann::json::object());
  } catch (const std::exception &e) {
    // TODO: Show error notification
    std::cerr << "Error: " << e.what() << std::endl;
  }
}