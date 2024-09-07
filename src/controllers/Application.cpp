#include "Application.hpp"
#include "CategoryView.hpp"
#include "CreateVault.hpp"
#include "MainScreen.hpp"
#include "VaultModel.hpp"
#include "gtkmm/box.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include "gtkmm/stack.h"
#include <iostream>

Application::Application() : Gtk::Application("com.example.yourdamapp") {
  loadCss();
}

void Application::on_activate() {
  auto mainWindow = Gtk::manage(new Gtk::Window());
  mainWindow->set_title("File Vault");
  mainWindow->set_default_size(1280, 720);

  auto stack = Gtk::manage(new Gtk::Stack());
  auto categoryView = Gtk::make_managed<CategoryView>(*mainWindow, "all");
  // Create the login and main screens as parts of the stack
  auto createVaultScreen = Gtk::manage(new CreateVault(*stack, *mainWindow));
  auto mainScreen = Gtk::manage(new MainScreen(*mainWindow, categoryView));
  mainScreen->set_size_request(1280, -1);
  mainScreen->set_name("main-screen");

  stack->add(*createVaultScreen, "createVaultScreen", "Create Vault");
  stack->add(*mainScreen, "main", "Main");

  VaultModel vault("../config.json");
  std::cout << "Vault Path:===" << vault.getPath() << std::endl;
  std::cout << "Vault Path:===" << vault.getName() << std::endl;
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
void Application::loadCss() {
  auto cssProvider = Gtk::CssProvider::create();
  std::string cssPath = "../styles.css";
  try {
    cssProvider->load_from_path(cssPath);
  } catch (const Gtk::CssParserError &ex) {
    throw std::runtime_error("Failed to load CSS: " + cssPath + "\n" +
                             ex.what());
  }

  Gtk::StyleProvider::add_provider_for_display(
      Gdk::Display::get_default(), cssProvider,
      GTK_STYLE_PROVIDER_PRIORITY_USER);
}