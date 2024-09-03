#include "CategoryView.hpp"
CategoryView::CategoryView(const std::string categoryId)
    : categoryViewLabel(categoryId), categoryId(categoryId) {

  append(categoryViewLabel);
};