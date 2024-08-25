#include "Application.hpp"
#include "CreateVault.hpp"
#include "MainScreen.hpp"
#include "VaultModel.hpp"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/stack.h"
#include "json.hpp"
#include "utils.hpp"

Application::Application() : Gtk::Application("com.example.yourdamapp") {}

void Application::on_activate() {
  auto mainWindow = Gtk::manage(new Gtk::Window());
  mainWindow->set_title("File Vault");
  mainWindow->set_default_size(1280, 720);

  auto stack = Gtk::manage(new Gtk::Stack());

  // Create the login and main screens as parts of the stack
  auto createVaultScreen = Gtk::manage(new CreateVault(*stack));
  auto mainScreen = Gtk::manage(new MainScreen());

  stack->add(*createVaultScreen, "createVaultScreen", "Create Vault");
  stack->add(*mainScreen, "main", "Main");

  // Check user login status
  nlohmann::json jsonData;

  VaultModel vault("../config.json");

  if (vault.getName().empty()) {
    stack->set_visible_child("createVaultScreen"); // Show login screen
  } else {
    stack->set_visible_child("main"); // Show main screen
  }

  // Add stack and switcher to main window
  auto vbox = Gtk::manage(new Gtk::Box(Gtk::Orientation::VERTICAL));
  vbox->append(*stack);

  mainWindow->set_child(*vbox);
  add_window(*mainWindow);
  mainWindow->present();
}