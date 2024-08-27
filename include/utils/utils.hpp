// LoginWindow.hpp
#pragma once
#include <string>
namespace Utils {
std::string generateId();
bool isIdInFile(const std::string &id);
void saveIdToFile(const std::string &id);
std::string getGeneratedIdsFilePath();
} // namespace Utils