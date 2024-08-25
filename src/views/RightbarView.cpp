#include "RightbarView.hpp"

RightbarView::RightbarView() : Gtk::Box(Gtk::Orientation::VERTICAL) {

  // Set the widget name for CSS identification
  set_name("rightbar");

  // Additional initialization code can go here
}

RightbarView::~RightbarView() {}