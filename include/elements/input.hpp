#pragma once

#include <gtkmm.h>
#include <sigc++/sigc++.h>

class Input : public Gtk::Box {
public:
  Input();
  virtual ~Input();

  // Setters and Getters
  void setText(const Glib::ustring &text);
  Glib::ustring getText() const;
  void setEditable(bool editable);
  bool isEditable() const;
  void setVisible(bool visible);
  bool isVisible() const;
  Gtk::Entry &getEntry(); // Add this getter

  // Signal to notify when the text changes
  sigc::signal<void(const Glib::ustring &)> signalTextChanged;

private:
  Gtk::Entry m_Entry;

  // Signal handlers
  void onTextChange();
};
