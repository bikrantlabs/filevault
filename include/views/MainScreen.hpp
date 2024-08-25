#pragma once
#include "CenterView.hpp"
#include "RightbarView.hpp"
#include "SidebarView.hpp"
#include "gtkmm/box.h"
#include <gtkmm/window.h>

class MainScreen : public Gtk::Box {
public:
  MainScreen();
  ~MainScreen() override;

protected:
  // Panes
  Gtk::Paned mainPaned;
  Gtk::Paned rightPaned;

  // Actual Views
  CenterView centerBox;
  SidebarView sidebar;
  RightbarView rightbar;

  // UI components
  Gtk::Box parent;
};
