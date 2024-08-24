#pragma once
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "input.hpp"
#include <gtkmm/window.h>

class MainScreen : public Gtk::Box {
public:
  MainScreen();
  ~MainScreen() override;

protected:
  Gtk::Button showDialog;
  Gtk::Box parent;
  Input input;
  void onInputTextChange(const Glib::ustring &text);
};
