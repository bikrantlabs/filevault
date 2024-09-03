#pragma once

#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#include <string>
#include <vector>

class CategoryListView : public Gtk::Grid {
public:
  CategoryListView();

private:
  std::vector<Gtk::Button *> categoryButtons;

  Gtk::Label categoryLabel;
  Gtk::Grid buttonContainer;
  void onCategoryButtonClicked(const std::string categoryId);
  void onCategoryAdded();
  void refreshCategoryList();
};