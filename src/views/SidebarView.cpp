#include "SidebarView.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "input.hpp"
#include <iostream>
void onIconButtonClick() { std::cout << "Clicked~"; }
SidebarView::SidebarView()
    : Gtk::Box(Gtk::Orientation::VERTICAL),
      addCategoryBtn("../folder-plus.png", onIconButtonClick), categoryInput() {
  categoryInput.disableSpecialCharacters();
  // Set background color for visual differentiation
  append(primaryActionButtonGrid);
  primaryActionButtonGrid.attach(categoryInput, 0, 0, 1, 1);
  primaryActionButtonGrid.attach(addCategoryBtn, 1, 0, 1, 1);
  categoryInput.signalEnterPressed.connect(
      sigc::mem_fun(*this, &SidebarView::onEnterPressed));
  categoryInput.signalTextChanged.connect(
      sigc::mem_fun(*this, &SidebarView::onTextChange));
  primaryActionButtonGrid.set_column_homogeneous(
      false); // Make all columns have the same width
  primaryActionButtonGrid.set_row_homogeneous(
      false); // Rows can have different heights
  set_name("sidebar");
  // Additional initialization code can go here
}
void SidebarView::onEnterPressed(const Glib::ustring &text) {
  try {
    FolderUtils::createCategoryFolder(text);
  } catch (const std::exception &e) {
    // TODO: Show error notification
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
SidebarView::~SidebarView() {}