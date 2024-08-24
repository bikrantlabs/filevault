#pragma once
#include "CreateVault.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "input.hpp"
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow();
  ~MainWindow() override;

protected:
  Gtk::Button showDialog;
  Gtk::Box parent;
  Input input;
  CreateVault createVault;
  void onInputTextChange(const Glib::ustring &text);
};
