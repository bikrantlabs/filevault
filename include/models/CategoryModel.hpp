#pragma once

#include "json.hpp"
#include <string>
#include <vector>

typedef struct CategoryMetadata {
  std::string id;
  std::string name;
  bool passwordLocked;
  std::string password;
  int noOfFiles;
} CategoryMetadata;

class CategoryModel {
public:
  CategoryModel();
  void addCategory(CategoryMetadata categoryMetadata);
  CategoryMetadata getCategoryById(int id);
  std::vector<CategoryMetadata> getAllCategories();
  ~CategoryModel();

private:
  void writeToFile() const;
  void loadExistingData();
  std::string filePath;
  nlohmann::json jsonData;
};