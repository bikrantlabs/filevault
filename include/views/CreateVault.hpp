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

  // // Setters and Getters
  // void setText(const Glib::ustring &text);
  // Glib::ustring getText() const;
  // void setEditable(bool editable);
  // bool isEditable() const;
  // void setVisible(bool visible);
  // bool isVisible() const;

  // Signal to notify when the button is clicked
  // sigc::signal<void(const Glib::ustring &)> signalTextChanged;
  void onButtonClick();
  bool saveVaultInfoToFile(const std::string& filePath, const std::string& vaultName, const std::string& vaultPath);

private:
  Gtk::Box wrapper;
  Input input;
  Gtk::Button createVaultBtn;
  Gtk::Stack &stack;
  Gtk::Window &mainWindow;
  // Signal handlers
};
