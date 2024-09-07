#pragma once

#include "CategoryListView.hpp"
#include "gtkmm/grid.h"
#include "icon_button.hpp"
#include "input.hpp"
#include <gtkmm.h>

class SidebarView : public Gtk::Grid {
public:
  SidebarView(Gtk::Window &parentWindow, CenterView *stack);
  ~SidebarView() override;
  // void setStack()

private:
  // Additional UI elements for the sidebar can be added here
  Gtk::Window &parentWindow;
  Gtk::Grid primaryActionButtonGrid;
  CenterView *stack;
  Input categoryInput;
  CategoryListView categoryList;
  IconButton addCategoryBtn;

  void onEnterPressed(const std::string &);
};
