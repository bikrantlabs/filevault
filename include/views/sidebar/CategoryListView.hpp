#pragma once

#include "CenterView.hpp"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#include <string>
#include <vector>

class CategoryListView : public Gtk::Grid {
public:
  CategoryListView(Gtk::Window &parentWindow, CenterView *stack);

private:
  Gtk::Window &parentWindow;
  std::vector<Gtk::Button *> categoryButtons;
  CenterView *stack;
  Gtk::Label categoryLabel;
  Gtk::Grid buttonContainer;
  void onCategoryButtonClicked(const std::string categoryId);
  void onCategoryAdded();
  void refreshCategoryList();
};