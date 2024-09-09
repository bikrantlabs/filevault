#pragma once

#include "AssetModel.hpp"
#include "json.hpp"
#include "sigc++/signal.h"
#include <string>
#include <vector>

typedef struct CategoryMetadata {
  std::string id;
  std::string name;
  std::string password;
  bool passwordLocked;
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
  CategoryMetadata getCategoryById(std::string id);
  std::vector<CategoryMetadata> getAllCategories();

  //
  std::vector<AssetModel> getAssetsByCategory(std::string categoryId);
  bool addAssetsToCategory(std::vector<AssetModel> assets,
                           std::string categoryId);
  void updateRootPath(std::string &path);
  void createDefaultCategories(std::string &path);
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
  nlohmann::json assetJsonData;
};