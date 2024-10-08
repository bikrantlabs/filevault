#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/centerbox.h"
#include "input.hpp"
#include <gtkmm.h>
#include <sigc++/sigc++.h>

class CreateVault : public Gtk::CenterBox {
public:
  CreateVault(Gtk::Stack &stack, Gtk::Window &mainWindow);
  ~CreateVault() override;

  bool saveVaultInfoToFile(const std::string &filePath,
                           const std::string &vaultName,
                           const std::string &vaultPath);
  void onEnterPressed(const Glib::ustring &text);
  sigc::signal<void()> signalVaultCreated;
  // TODO: Implement initialize required metadata.jsons
  void initializeMetadatas();

private:
  Gtk::Box wrapper;
  Input input;
  Gtk::Button createVaultBtn;
  Gtk::Stack &stack;
  Gtk::Window &mainWindow;
  // Signal handlers
};
