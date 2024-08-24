#include "MainScreen.hpp"
#include "sigc++/functors/mem_fun.h"
#include <gtkmm/box.h>
#include <iostream>

MainScreen::MainScreen() : showDialog("Show Dialog"), input() {

  input.setText("hello world");
  input.signalTextChanged.connect(
      sigc::mem_fun(*this, &MainScreen::onInputTextChange));
  parent.set_orientation(Gtk::Orientation::VERTICAL);
  parent.append(input);
  parent.append(showDialog);
  parent.set_spacing(10);
  parent.set_margin(10);

  append(parent);
}
void MainScreen::onInputTextChange(const Glib::ustring &text) {
  std::cout << "Input text changed: " << text << std::endl;
}
MainScreen::~MainScreen() {}
