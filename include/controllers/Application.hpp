#pragma once
#include <gtkmm/application.h>

class Application : public Gtk::Application {
public:
  Application();

protected:
  void on_activate() override;
  Gtk::Window *parentW;
};
