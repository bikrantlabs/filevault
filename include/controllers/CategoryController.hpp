#pragma once
#include <string>
class CategoryController {

public:
  CategoryController();

  void onAddCategory(const std::string &categoryName,
                     const std::string &password);
};