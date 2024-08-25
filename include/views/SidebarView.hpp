#pragma once

#include <gtkmm.h>

class SidebarView : public Gtk::Box {
public:
  SidebarView();
  ~SidebarView() override;

private:
  // Additional UI elements for the sidebar can be added here
};
