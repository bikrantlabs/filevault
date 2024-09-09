#include "CreateVault.hpp"
#include "CategoryModel.hpp"
#include "DirectoryDialog.hpp"
#include "FileUtils.hpp"
#include "FolderUtils.hpp"
#include "VaultModel.hpp"
#include "constants.hpp"
#include "gtkmm/centerbox.h"
#include "gtkmm/enums.h"
#include "json.hpp"
#include <iostream>

CreateVault::CreateVault(Gtk::Stack &stack, Gtk::Window &mainWindow)
    : input(), Gtk::CenterBox(), stack(stack), mainWindow(mainWindow) {
  input.disableSpecialCharacters();
  input.signalEnterPressed.connect(
      sigc::mem_fun(*this, &CreateVault::onEnterPressed));
  input.setText("Enter your vault name");
  wrapper.set_orientation(Gtk::Orientation::VERTICAL);
  wrapper.set_spacing(10);
  wrapper.append(input);
  // Make CreateVault Box take entire width/height of the screen
  set_vexpand(true);
  set_hexpand(true);

  // Align self to the center of the screen
  set_halign(Gtk::Align::CENTER);
  set_valign(Gtk::Align::CENTER);
  set_center_widget(wrapper);
}

void CreateVault::onEnterPressed(const Glib::ustring &text) {
  std::string vaultName = input.getText();
  std::cout << "ℹ️[CreateVault.cpp:30] Info : " << "Creating Vault..."
            << std::endl;
  // Create and show the directory dialog using DirectoryDialog
  auto dialog = Gtk::manage(new DirectoryDialog(
      mainWindow,
      [this, vaultName](const std::string &path) {
        std::string folderPath = path + "/" + vaultName;
        try {
          // Create Vault Folder
          FolderUtils::createFolder(folderPath);

          // Save vault data to config.json
          VaultModel vault(vaultName, folderPath);
          nlohmann::json vaultJson = vault.toJson();
          FileUtils::saveJsonToFile(ROOT_CONFIG_PATH, vaultJson);

          CategoryModel::getInstance().updateRootPath(folderPath);
          CategoryModel::getInstance().createDefaultCategories(folderPath);
          input.setText("");
          // Navigate to main screen
          signalVaultCreated.emit();
          stack.set_visible_child("main");
        } catch (const std::exception &e) {
          std::cerr << "🛑[CreateVault.cpp:42] Error : " << e.what()
                    << std::endl;
        }
      },
      [](const std::string &message) {
        std::cout << "Error: " << message << std::endl;
      }));

  dialog->show();
}

CreateVault::~CreateVault() {}