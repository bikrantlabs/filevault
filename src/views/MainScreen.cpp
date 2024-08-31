#include "MainScreen.hpp"
#include "RightbarView.hpp"
#include "SidebarView.hpp"
#include <gtkmm/box.h>

MainScreen::MainScreen() : sidebar(), centerBox(), rightbar() {

  parent.set_orientation(Gtk::Orientation::HORIZONTAL);

  // Set Widths
  sidebar.set_size_request(256, -1); // 20% of the window width for the sidebar
  centerBox.set_size_request(
      768, -1); // 60% of the window width for the main content
  rightbar.set_size_request(256, -1);

  // Only allow centerBox to expand
  centerBox.set_expand(true);

  sidebar.set_expand(false);
  rightbar.set_expand(false);
  // Append views inside parent
  parent.append(sidebar);
  parent.append(centerBox);
  parent.append(rightbar);

  // Append parent itself into mainscreen
  append(parent);
}
MainScreen::~MainScreen() {}
