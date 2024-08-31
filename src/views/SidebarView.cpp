#include "SidebarView.hpp"
#include "CategoryController.hpp"
#include "input.hpp"
#include <iostream>
void onIconButtonClick() { std::cout << "Clicked~"; }
SidebarView::SidebarView()
    : addCategoryBtn("../assets/folder-plus.png", onIconButtonClick),
      categoryInput() {
  categoryInput.disableSpecialCharacters();

  attach(primaryActionButtonGrid, 0, 0, 1, 1);
  attach(categoryList, 0, 1, 1, 1);
  set_row_spacing(32);

  primaryActionButtonGrid.attach(categoryInput, 0, 0, 1, 1);
  primaryActionButtonGrid.attach(addCategoryBtn, 1, 0, 1, 1);
  primaryActionButtonGrid.set_column_homogeneous(
      false); // Make all columns have the same width
  primaryActionButtonGrid.set_row_homogeneous(
      false); // Rows can have different heights

  categoryInput.signalEnterPressed.connect(
      sigc::mem_fun(*this, &SidebarView::onEnterPressed));
  set_name("sidebar");
  // Additional initialization code can go here
}
void SidebarView::onEnterPressed(const std::string &text) {
  CategoryController categoryController;
  categoryController.onAddCategory(text, "");
  categoryInput.setText("");
}
SidebarView::~SidebarView() {}