#include "SidebarView.hpp"

SidebarView::SidebarView() : Gtk::Box(Gtk::Orientation::VERTICAL) {

  // Set background color for visual differentiation
  set_name("sidebar");
  // Additional initialization code can go here
}

SidebarView::~SidebarView() {}