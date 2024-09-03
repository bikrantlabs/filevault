#include "sidebar/CategoryListView.hpp"
#include "CategoryModel.hpp"
#include "CategoryView.hpp"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include <iostream>
#include <string>

CategoryListView::CategoryListView(CenterView *stack)
    : categoryLabel("Categories"), stack(stack) {
  stack->set_visible_child("all-files");
  CategoryModel &categoryModel = CategoryModel::getInstance();
  categoryModel.signalCategoryAdded.connect(
      sigc::mem_fun(*this, &CategoryListView::onCategoryAdded));
  auto categories = categoryModel.getAllCategories();

  // Setup List UI
  refreshCategoryList();

  buttonContainer.set_hexpand(true);
  buttonContainer.set_vexpand(true);
  buttonContainer.set_name("category-btn-container");
  buttonContainer.set_row_spacing(6);
  buttonContainer.set_column_homogeneous(true);

  categoryLabel.set_name("label");
  categoryLabel.set_margin_bottom(12);

  attach(categoryLabel, 0, 0, 1, 1);
  attach(buttonContainer, 0, 1, 1, 1);

  // set_halign(Gtk::Align::START);
  set_name("category-list");
  // categoryModel.
}
void CategoryListView::refreshCategoryList() {

  // Remove buttons and reload them
  for (auto buttons : categoryButtons) {
    buttons->unparent();
  }
  categoryButtons.clear();

  CategoryModel &categoryModel = CategoryModel::getInstance();
  auto categories = categoryModel.getAllCategories();
  int row = 0;
  for (const auto &category : categories) {
    // Create a button
    auto categoryButton = Gtk::make_managed<Gtk::Button>(category.name);
    auto label = Gtk::make_managed<Gtk::Label>(category.name);
    auto numberLabel = Gtk::make_managed<Gtk::Label>("5");

    auto folderIcon = Gtk::make_managed<Gtk::Image>("../assets/folder.png");

    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 6);

    numberLabel->set_name("btn-number-label");

    hbox->append(*folderIcon);
    hbox->append(*label);

    if (category.passwordLocked) {
      auto lockIcon = Gtk::make_managed<Gtk::Image>("../assets/lock.png");
      hbox->append(*lockIcon);
      lockIcon->set_halign(Gtk::Align::END);
      lockIcon->add_css_class("lock-icon");
    }

    hbox->append(*numberLabel);
    hbox->set_valign(Gtk::Align::CENTER);

    label->set_hexpand();
    label->set_halign(Gtk::Align::START);

    numberLabel->set_halign(Gtk::Align::END);

    categoryButton->set_child(*hbox);
    categoryButton->set_size_request(-1, 32);
    categoryButton->set_valign(Gtk::Align::CENTER);
    categoryButton->signal_clicked().connect([this, category]() {
      onCategoryButtonClicked(category.id); // Pass the category ID
    });
    categoryButton->set_name("category-btn");

    // Change cursor to pointer (hand) on hover
    categoryButton->set_cursor("pointer");
    categoryButtons.push_back(categoryButton);

    // Add buttons to container
    buttonContainer.attach(*categoryButton, 0, row, 1, 1);

    row++;
  }
}

void CategoryListView::onCategoryButtonClicked(const std::string categoryId) {
  // TODO: Navigate to that category screen
  // Create or load the category-specific screen in the stack
  std::string screenName = "category-" + categoryId;
  if (!stack->get_child_by_name(screenName)) {
    auto categoryView = Gtk::make_managed<CategoryView>(categoryId);
    stack->add(*categoryView, screenName, "Category");
  }

  // Switch to the corresponding category screen
  stack->set_visible_child(screenName);

  std::cout << "Navigated to category ID: " << categoryId << std::endl;
}

void CategoryListView::onCategoryAdded() { refreshCategoryList(); }