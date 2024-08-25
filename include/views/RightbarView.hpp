#pragma once

#include <gtkmm.h>

class RightbarView : public Gtk::Box {
public:
  RightbarView();
  ~RightbarView() override;

private:
  // Additional UI elements for the rightbar can be added here
};
