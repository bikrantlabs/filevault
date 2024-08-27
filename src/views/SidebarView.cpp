#include "SidebarView.hpp"
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "input.hpp"
#include "utils.hpp"
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
  primaryActionButtonGrid.set_column_homogeneous(
      false); // Make all columns have the same width
  primaryActionButtonGrid.set_row_homogeneous(
      false); // Rows can have different heights
  set_name("sidebar");
  // Additional initialization code can go here
}
void SidebarView::onEnterPressed(const std::string &text) {
  try {
    FolderUtils::createCategoryFolder(text);

    VaultModel vault("../config.json");
    // Create category metadata.json

    // Add created category data to root metadata.json
    std::string uniqueId = Utils::generateId();
    CategoryMetadata categoryMetadata = {uniqueId, text, true, "password1234"};
    auto categoryModel = CategoryModel(vault.getPath() + "/" + "metadata.json");
    categoryModel.addCategory(categoryMetadata);
    categoryInput.setText("");

    // Create an empty metadatsa.json insdie that  category
    std::filesystem::path _metadata =
        std::filesystem::path(vault.getPath()) / text / "metadata.json";
    FileUtils::saveJsonToFile(_metadata, nlohmann::json::object());
  } catch (const std::exception &e) {
    // TODO: Show error notification
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
SidebarView::~SidebarView() {}