#pragma once

#include "gtkmm/grid.h"
#include "icon_button.hpp"
#include "input.hpp"
#include <gtkmm.h>

class SidebarView : public Gtk::Box {
public:
  SidebarView();
  ~SidebarView() override;

private:
  // Additional UI elements for the sidebar can be added here
  Gtk::Grid primaryActionButtonGrid;
  Input categoryInput;
  IconButton addCategoryBtn;

  void onEnterPressed(const Glib::ustring &);
};
