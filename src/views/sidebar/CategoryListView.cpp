#include "sidebar/CategoryListView.hpp"
#include "CategoryModel.hpp"
#include "CategoryView.hpp"
#include "CreateVault.hpp"
#include "FileUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include <iostream>
#include <string>

CategoryListView::CategoryListView(Gtk::Window &parentWindow, CenterView *stack,
                                   CreateVault &createVaultView)
    : parentWindow(parentWindow), createVaultView(createVaultView),
      categoryLabel("Categories"), stack(stack) {
  createVaultView.signalVaultCreated.connect(
      sigc::mem_fun(*this, &CategoryListView::renderDefaultCategories));
  CategoryModel &categoryModel = CategoryModel::getInstance();
  categoryModel.signalCategoryAdded.connect(
      sigc::mem_fun(*this, &CategoryListView::onCategoryAdded));
  auto categories = categoryModel.getAllCategories();
  // Setup List UI
  refreshCategoryList();
  renderDefaultCategories();

  buttonContainer.set_hexpand(true);
  buttonContainer.set_vexpand(true);
  buttonContainer.set_name("category-btn-container");
  buttonContainer.set_row_spacing(6);
  buttonContainer.set_column_homogeneous(true);
  defaultCategoriesContainer.set_row_spacing(6);

  categoryLabel.set_name("label");
  categoryLabel.set_margin_bottom(12);

  categoryLabel.set_margin_top(32);
  attach(defaultCategoriesContainer, 0, 0, 1, 1);
  attach(categoryLabel, 0, 1, 1, 1);
  attach(buttonContainer, 0, 2, 1, 1);

  // set_halign(Gtk::Align::START);
  set_name("category-list");
  // categoryModel.
}

void CategoryListView::renderDefaultCategories() {
  CategoryModel &categoryModel = CategoryModel::getInstance();
  auto defaultCategories = categoryModel.getDefaultCategories();
  int row = 0;
  for (const auto &category : defaultCategories) {
    auto categoryButton = Gtk::make_managed<Gtk::Button>(category.name);

    auto label = Gtk::make_managed<Gtk::Label>(category.name);
    auto numberLabel = Gtk::make_managed<Gtk::Label>("5");
    std::cout << "🟢 [CategoryListView.cpp:54]: " << "Icon Paths====="
              << category.iconPath << std::endl;
    auto folderIcon = Gtk::make_managed<Gtk::Image>(category.iconPath);

    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 6);

    numberLabel->set_name("btn-number-label");

    hbox->append(*folderIcon);
    hbox->append(*label);
    hbox->append(*numberLabel);
    hbox->set_valign(Gtk::Align::CENTER);

    label->set_hexpand();
    label->set_halign(Gtk::Align::START);

    numberLabel->set_halign(Gtk::Align::END);

    categoryButton->set_child(*hbox);
    categoryButton->set_size_request(-1, 32);
    categoryButton->set_valign(Gtk::Align::CENTER);
    categoryButton->signal_clicked().connect(
        [this, category, categoryButton]() {
          onCategoryButtonClicked(categoryButton,
                                  category.name); // Pass the category ID
        });
    categoryButton->set_name("category-btn");

    // Change cursor to pointer (hand) on hover
    categoryButton->set_cursor("pointer");
    defaultCategoriesButtons.push_back(categoryButton);

    // Add buttons to container
    defaultCategoriesContainer.attach(*categoryButton, 0, row, 1, 1);

    row++;
  }
}

void CategoryListView::refreshCategoryList() {
  VaultModel vaultModel(ROOT_CONFIG_PATH);
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

    auto folderIcon = Gtk::make_managed<Gtk::Image>(category.iconPath);

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
    categoryButton->signal_clicked().connect(
        [this, category, categoryButton]() {
          onCategoryButtonClicked(categoryButton,
                                  category.name); // Pass the category ID
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

void CategoryListView::onCategoryButtonClicked(Gtk::Button *button,
                                               const std::string categoryName) {
  // TODO: Navigate to that category screen
  // Create or load the category-specific screen in the stack
  std::string screenName = categoryName;
  if (!stack->get_child_by_name(screenName)) {
    auto categoryView =
        Gtk::make_managed<CategoryView>(parentWindow, categoryName);
    stack->add(*categoryView, screenName, "Category");
  }
  // TODO: add active screen in config.json
  VaultModel vaultModel(ROOT_CONFIG_PATH);
  vaultModel.setActiveScreen(screenName);
  nlohmann::json vaultJson = vaultModel.toJson();
  FileUtils::saveJsonToFile(ROOT_CONFIG_PATH, vaultJson);

  // Remove active-category from other buttons
  for (auto buttons : categoryButtons) {
    buttons->remove_css_class("active-category");
  }
  for (auto buttons : defaultCategoriesButtons) {
    buttons->remove_css_class("active-category");
  }
  if (vaultModel.getActiveScreen() == categoryName) {
    button->add_css_class("active-category");

  } else {
    button->remove_css_class("active-category");
  }
  // Switch to the corresponding category screen
  stack->set_visible_child(screenName);
}

void CategoryListView::onCategoryAdded() { refreshCategoryList(); }