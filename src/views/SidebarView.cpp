#include "SidebarView.hpp"
#include <iostream>
void onIconButtonClick() { std::cout << "Clicked~"; }
SidebarView::SidebarView()
    : Gtk::Box(Gtk::Orientation::VERTICAL),
      addCategoryBtn("../folder-plus.png", onIconButtonClick) {

  // Set background color for visual differentiation
  append(primaryActionButtonGrid);
  primaryActionButtonGrid.attach(addCategoryBtn, 0, 0, 1, 1);
  primaryActionButtonGrid.set_column_homogeneous(
      false); // Make all columns have the same width
  primaryActionButtonGrid.set_row_homogeneous(
      false); // Rows can have different heights
  set_name("sidebar");
  // Additional initialization code can go here
}

SidebarView::~SidebarView() {}