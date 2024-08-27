#pragma once

#include "json.hpp"
#include <string>

typedef struct CategoryMetadata {
  std::string id;
  std::string name;
  bool passwordLocked;
  std::string password;
} CategoryMetadata;

class CategoryModel {
public:
  CategoryModel();
  CategoryModel(const std::string &path);
  void addCategory(CategoryMetadata categoryMetadata);
  CategoryMetadata getCategoryById(int id);
  ~CategoryModel();

private:
  void writeToFile() const;
  void loadExistingData();
  std::string filePath;
  nlohmann::json jsonData;
};