#pragma once

#include "gtkmm/box.h"
#include "input.hpp"
#include <string>
class CategoryView : public Gtk::Box {
public:
  std::string onPressEnter();

private:
  Gtk::Button createCategory;
  Gtk::Box parent;
  Input input;
  void onInputTextChange(const Glib::ustring &text);
};