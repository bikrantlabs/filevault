#ifndef FOLDER_UTILS_HPP
#define FOLDER_UTILS_HPP

#include <string>
/**
 * We don't need a class for our utils since we won't be making any instances of
 * them, we could directly user FolderUtils namespace
 */
namespace FolderUtils {

/**
 * Creates a folder at the specified path with the given name.
 *
 * @param path The path where the folder should be created.
 * @param folderName The name of the folder to be created.
 * @return true if the folder was created successfully, false otherwise.
 */
bool createFolder(const std::string &path, const std::string &folderName);

/**
 * Moves a folder from source path to destination path.
 *
 * @param srcPath The path of the folder to be moved.
 * @param destPath The destination path where the folder should be moved.
 * @return true if the folder was moved successfully, false otherwise.
 */
bool moveFolder(const std::string &srcPath, const std::string &destPath);

/**
 * Deletes a folder at the specified path.
 *
 * @param path The path of the folder to be deleted.
 * @return true if the folder was deleted successfully, false otherwise.
 */
bool deleteFolder(const std::string &path);

} // namespace FolderUtils

#endif // FOLDER_UTILS_HPP
