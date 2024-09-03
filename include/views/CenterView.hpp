#pragma once

#include "CategoryView.hpp"
#include "gtkmm/stack.h"
#include <gtkmm.h>

class CenterView : public Gtk::Stack {
public:
  CenterView(CategoryView *categoryView);
  ~CenterView() override;

private:
  CategoryView *categoryView;
  // Additional UI elements for the center view can be added here
};
