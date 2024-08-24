#include "CreateVault.hpp"
#include "gtkmm/centerbox.h"
#include "gtkmm/enums.h"
#include <iostream>

CreateVault::CreateVault()
    : createVaultBtn("Create Vault"), input(), Gtk::CenterBox() {
  createVaultBtn.signal_clicked().connect(
      sigc::mem_fun(*this, &CreateVault::onButtonClick));
  input.setText("Enter your vault name");
  wrapper.set_orientation(Gtk::Orientation::VERTICAL);
  wrapper.set_spacing(10);
  wrapper.append(input);
  wrapper.append(createVaultBtn);

  // Make CreateVault Box take entire width/height of the screen
  set_vexpand(true);
  set_hexpand(true);

  // Align self to the center of the screen
  set_halign(Gtk::Align::CENTER);
  set_valign(Gtk::Align::CENTER);
  set_center_widget(wrapper);
}

void CreateVault::onButtonClick() {
  std::cout << "Input: " << input.getText() << std::endl;
}

CreateVault::~CreateVault() {}