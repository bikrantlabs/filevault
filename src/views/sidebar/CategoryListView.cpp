#include "sidebar/CategoryListView.hpp"
#include "CategoryModel.hpp"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include <iostream>

CategoryListView::CategoryListView() : categoryLabel("Categories") {
  CategoryModel categoryModel;
  auto categories = categoryModel.getAllCategories();
  std::cout << "🟢 [CategoryListView.cpp:9]: " << "CategoryListView"
            << std::endl;
  int row = 0;

  for (auto &category : categories) {

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
    categoryButton->signal_clicked().connect(
        sigc::mem_fun(*this, &CategoryListView::onCategoryButtonClicked));
    categoryButton->set_name("category-btn");

    // Change cursor to pointer (hand) on hover
    categoryButton->set_cursor("pointer");

    // Add buttons to container
    buttonContainer.attach(*categoryButton, 0, row, 1, 1);

    row++;
  }

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
}

void CategoryListView::onCategoryButtonClicked() {

  std::cout << "Category clicked: " << std::endl;
}