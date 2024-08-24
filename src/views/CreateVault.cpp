#include "CreateVault.hpp"
#include "DirectoryDialog.hpp"
#include "gtkmm/centerbox.h"
#include "gtkmm/enums.h"
#include "utils.hpp"
#include <iostream>

CreateVault::CreateVault(Gtk::Stack &stack, Gtk::Window &mainWindow)
    : createVaultBtn("Create Vault"), input(), Gtk::CenterBox(), stack(stack),
      mainWindow(mainWindow) {
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
  std::string username = input.getText();

  // Create and show the directory dialog using DirectoryDialog
  auto dialog = Gtk::manage(new DirectoryDialog(
      mainWindow,
      [this, username](const std::string &path) {
        saveUserName(username);
        std::cout << "Directory selected: " << path << std::endl;
        stack.set_visible_child("main");
      },
      [](const std::string &message) {
        std::cout << "Error: " << message << std::endl;
      }));

  dialog->show();
}

CreateVault::~CreateVault() {}