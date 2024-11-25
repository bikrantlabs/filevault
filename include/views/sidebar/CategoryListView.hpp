#pragma once

#include "CenterView.hpp"
#include "CreateVault.hpp"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#include <string>
#include <vector>

class CategoryListView : public Gtk::Grid {
public:
  CategoryListView(Gtk::Window &parentWindow, CenterView *stack,
                   CreateVault &createVaultView);

private:
  Gtk::Window &parentWindow;
  std::vector<Gtk::Button *> categoryButtons;
  std::vector<Gtk::Button *> defaultCategoriesButtons;

  CreateVault &createVaultView;
  CenterView *stack;
  Gtk::Label categoryLabel;
  Gtk::Grid buttonContainer;
  Gtk::Grid defaultCategoriesContainer;
  void onCategoryButtonClicked(Gtk::Button *button,
                               const std::string categoryName,
                               const std::string categoryId);
  void onCategoryAdded();
  void refreshCategoryList();
  void renderDefaultCategories();
};