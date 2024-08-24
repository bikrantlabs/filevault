#pragma once

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/centerbox.h"
#include "input.hpp"
#include <gtkmm.h>
#include <sigc++/sigc++.h>

class CreateVault : public Gtk::CenterBox {
public:
  CreateVault();
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

private:
  Gtk::Box wrapper;
  Input input;
  Gtk::Button createVaultBtn;
  // Signal handlers
};
