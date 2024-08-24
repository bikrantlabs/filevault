#include "CreateVault.hpp"
#include "DirectoryDialog.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "gtkmm/centerbox.h"
#include "gtkmm/enums.h"
#include "json.hpp"
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
  std::string vaultName = input.getText();

  // Create and show the directory dialog using DirectoryDialog
  auto dialog = Gtk::manage(new DirectoryDialog(
      mainWindow,
      [this, vaultName](const std::string &path) {
        std::string folderPath = path + "/" + vaultName;
        if (FolderUtils::createFolder(path, vaultName)) {

          VaultModel vault(vaultName, folderPath);
          nlohmann::json vaultJson = vault.toJson();

          if (!FileUtils::saveJsonToFile("../config.json", vaultJson)) {
            std::cout << "Failed to save vault information." << std::endl;
          }

          stack.set_visible_child("main");
        } else {
          std::cout << "Failed to create folder: " << folderPath << std::endl;
        }
      },
      [](const std::string &message) {
        std::cout << "Error: " << message << std::endl;
      }));

  dialog->show();
}

CreateVault::~CreateVault() {}