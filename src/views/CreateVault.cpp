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

  // Create and show the directory dialog
  auto dialog = Gtk::manage(new DirectoryDialog(mainWindow));
  //

  dialog->signal_response().connect([this, dialog, username](int response_id) {
    if (response_id == Gtk::ResponseType::OK) {
      auto file = dialog->get_file();
      if (!file) {
        // TODO: Show notification
        std::cout << "No directory selected" << std::endl;
        dialog->hide();
        return;
      }
      auto path = dialog->get_file()->get_path();
      saveUserName(username);
      stack.set_visible_child("main");
    } else {
      std::cout << "Dialog was canceled." << std::endl;
    }
    dialog->hide();
  }

  );

  dialog->show();
}

CreateVault::~CreateVault() {}