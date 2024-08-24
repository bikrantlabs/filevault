#include "FolderUtils.hpp"
#include <filesystem>
#include <iostream>

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

} // namespace FolderUtils
