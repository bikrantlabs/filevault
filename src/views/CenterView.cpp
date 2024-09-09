#include "CenterView.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "gtkmm/object.h"
#include <iostream>

CenterView::CenterView(Gtk::Window &parentWindow, CategoryView *categoryView)
    : categoryView(categoryView), parentWindow(parentWindow) {

  // Set the widget name for CSS identification
  VaultModel vaultModel(ROOT_CONFIG_PATH);
  set_name("center-view");
  auto allFiles = Gtk::make_managed<CategoryView>(parentWindow, "all");
  add(*allFiles, "all", "Category");

  auto trash = Gtk::make_managed<CategoryView>(parentWindow, "trash");
  add(*trash, "trash", "Category");

  auto uncategorized =
      Gtk::make_managed<CategoryView>(parentWindow, "uncategorized");
  add(*uncategorized, "uncategorized", "Category");

  auto untagged = Gtk::make_managed<CategoryView>(parentWindow, "untagged");
  add(*untagged, "untagged", "Category");

  auto tags = Gtk::make_managed<CategoryView>(parentWindow, "tags");
  add(*tags, "tags", "Category");
  if (vaultModel.getActiveScreen().empty()) {
    std::cout << "🟢 [CenterView.cpp:28]: " << "Navigating to all.."
              << std::endl;
    set_visible_child("all");

  } else {
    std::cout << "🟢 [CenterView.cpp:32]: " << "Navigating to "
              << vaultModel.getActiveScreen() << std::endl;
    set_visible_child(vaultModel.getActiveScreen());
  }
  // set_size_request();
  // set_halign(Gtk::Align::START);
  // set_valign(Gtk::Align::START);

  // set_vexpand();
  // set_hexpand();
  // Additional initialization code can go here
}

CenterView::~CenterView() {}