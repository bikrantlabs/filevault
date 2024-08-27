#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include <filesystem>
#include <iostream>
#include <stdexcept>

/**
 * We don't need a class for our utils since we won't be making any instances of
 * them, we could directly user FolderUtils namespace
 */
namespace FolderUtils {

bool createFolder(const std::string &path, const std::string &folderName) {
  try {
    std::filesystem::path folderPath = std::filesystem::path(path) / folderName;
    return std::filesystem::create_directory(folderPath);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error creating folder: " << e.what() << std::endl;
    return false;
  }
}

bool moveFolder(const std::string &srcPath, const std::string &destPath) {
  try {
    std::filesystem::rename(srcPath, destPath);
    return true;
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error moving folder: " << e.what() << std::endl;
    return false;
  }
}

bool deleteFolder(const std::string &path) {
  try {
    std::filesystem::remove_all(path);
    return true;
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error deleting folder: " << e.what() << std::endl;
    return false;
  }
}
bool checkFolderExists(const std::string &folderPath) {
  if (std::filesystem::exists(folderPath))
    return true;
  return false;
}
// TODO: throw error instead of returning
bool createCategoryFolder(const std::string &categoryName) {
  VaultModel vault("../config.json");
  if (vault.getPath().empty()) {
    throw std::runtime_error("Unable to get vault path.");
  }
  if (FolderUtils::isReservedFolderName(categoryName)) {
    throw std::runtime_error("This name cannot be taken. Enter a new name!");
  }
  std::filesystem::path directoryPath = vault.getPath() + "/" + categoryName;
  if (FolderUtils::checkFolderExists(directoryPath)) {

    throw std::runtime_error("Directory " + directoryPath.string() +
                             " already exists!");
  }
  std::filesystem::create_directory(directoryPath);
  return true;
}

bool isReservedFolderName(const std::string &text) {
  std::string textStr = text;
  std::transform(textStr.begin(), textStr.end(), textStr.begin(),
                 ::toupper); // Case insensitive
  return RESERVED_FILENAMES.find(textStr) != RESERVED_FILENAMES.end();
}
} // namespace FolderUtils
