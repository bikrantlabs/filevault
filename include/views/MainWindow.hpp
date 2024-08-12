#pragma once
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow();

private:
  void setup_ui();
};
