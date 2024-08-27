#pragma once

#include "gdkmm/event.h"
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

  void disableSpecialCharacters();
  void enableSpecialCharacters();
  bool specialCharactersAllowed() const;

  bool isReservedFileName(const Glib::ustring &text);
  bool containsForbiddenChars(const char c) const;
  Gtk::Entry &getEntry(); // Add this getter

  /**
   * Signal to notify when the text changes.

   * The `onTextChange()` method is connected to signal_changed().connect() of
   Input.

   * The `onTextChange()` is hereby responsible to emit the signal
   `signalTextChanged.emit(data)` with the `data` to be passed to the  receiver.

   * In the user class, the signal can be received through

   `Input::signalTextChanged.connect(sigc::mem_fun(*this,
   &UserClass::onInputTextChanged))` where `onInputTextChanged` is custom method
   defined

   in `UserClass` with `(data)` as argument
   */
  sigc::signal<void(const Glib::ustring &)> signalTextChanged;

  // Sigal to notify when enter is pressed
  sigc::signal<void(const Glib::ustring &)> signalEnterPressed;

private:
  Gtk::Entry m_Entry;
  bool allowSpecialCharacters;

  void connectSignals();
  void onKeyPressEvent();
  void onTextChange();
};
