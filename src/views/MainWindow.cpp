#include "MainWindow.hpp"
#include "CreateVault.hpp"
#include "sigc++/functors/mem_fun.h"
#include <gtkmm/box.h>
#include <iostream>

MainWindow::MainWindow() : showDialog("Show Dialog"), input(), createVault() {

  input.setText("hello world");
  input.signalTextChanged.connect(
      sigc::mem_fun(*this, &MainWindow::onInputTextChange));
  parent.set_orientation(Gtk::Orientation::VERTICAL);
  // parent.append(input);
  // parent.append(showDialog);
  parent.append(createVault);
  parent.set_spacing(10);
  parent.set_margin(10);

  set_child(parent);
  set_title("File Vault");
  set_default_size(1280, 720);
}
void MainWindow::onInputTextChange(const Glib::ustring &text) {
  std::cout << "Input text changed: " << text << std::endl;
}
MainWindow::~MainWindow() {}
