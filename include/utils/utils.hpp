// LoginWindow.hpp
#pragma once
#include <string>
#include <vector>
namespace Utils {
std::string generateId();
bool isIdInFile(const std::string &id);
void saveIdToFile(const std::string &id);
std::string getGeneratedIdsFilePath();
bool isStringInArray(const std::vector<std::string> &vec,
                     const std::string &value);
std::string formatSize(long long bytes);

} // namespace Utils