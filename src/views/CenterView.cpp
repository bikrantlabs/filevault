#include "CenterView.hpp"

CenterView::CenterView() : Gtk::Box(Gtk::Orientation::VERTICAL) {

  // Set the widget name for CSS identification
  set_name("center-view");

  // Additional initialization code can go here
}

CenterView::~CenterView() {}