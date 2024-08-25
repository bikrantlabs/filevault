#pragma once

#include <gtkmm.h>

class CenterView : public Gtk::Box {
public:
  CenterView();
  ~CenterView() override;

private:
  // Additional UI elements for the center view can be added here
};
