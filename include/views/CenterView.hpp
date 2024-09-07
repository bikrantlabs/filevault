#pragma once

#include "CategoryView.hpp"
#include "gtkmm/stack.h"
#include <gtkmm.h>

class CenterView : public Gtk::Stack {
public:
  CenterView(Gtk::Window &parentWindow, CategoryView *categoryView);
  ~CenterView() override;

private:
  Gtk::Window &parentWindow;
  CategoryView *categoryView;
  // Additional UI elements for the center view can be added here
};
