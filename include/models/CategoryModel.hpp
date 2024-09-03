#pragma once

#include "json.hpp"
#include "sigc++/signal.h"
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
  // A singleton instance of categorymodel across the app
  static CategoryModel &getInstance() {
    static CategoryModel instance;
    return instance;
  }

  void addCategory(CategoryMetadata categoryMetadata);
  CategoryMetadata getCategoryById(int id);
  std::vector<CategoryMetadata> getAllCategories();

  sigc::signal<void()> signalCategoryAdded;

private:
  // Private constructors
  CategoryModel();
  ~CategoryModel();
  // Prevent copying and assignment
  CategoryModel(const CategoryModel &) = delete;
  CategoryModel &operator=(const CategoryModel &) = delete;
  void writeToFile() const;
  void loadExistingData();
  std::string filePath;
  nlohmann::json jsonData;
};