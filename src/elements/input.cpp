#include "input.hpp"
#include "constants.hpp"
#include "glibmm/ustring.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>

Input::Input() : Gtk::Box(Gtk::Orientation::VERTICAL) {
  m_Entry.set_max_length(16);
  connectSignals();

  append(m_Entry);
}

Input::~Input() {}

void Input::setText(const Glib::ustring &text) { m_Entry.set_text(text); }

Glib::ustring Input::getText() const { return m_Entry.get_text(); }

Gtk::Entry &Input::getEntry() { return m_Entry; }

void Input::setEditable(bool editable) { m_Entry.set_editable(editable); }

bool Input::isEditable() const { return m_Entry.get_editable(); }

bool Input::containsForbiddenChars(const char c) const {
  return std::find(FORBIDDEN_CHARS.begin(), FORBIDDEN_CHARS.end(), c) !=
         FORBIDDEN_CHARS.end();
}
void Input::enableSpecialCharacters() { allowSpecialCharacters = true; }
void Input::disableSpecialCharacters() { allowSpecialCharacters = false; }
bool Input::specialCharactersAllowed() const { return allowSpecialCharacters; }

void Input::setVisible(bool visible) { m_Entry.set_visibility(visible); }

bool Input::isVisible() const { return m_Entry.get_visibility(); }

void Input::onTextChange() {
  Glib::ustring filteredText;
  Glib::ustring currentText = getText();

  // Filter forbidden characters
  if (!allowSpecialCharacters) {
    for (char c : currentText) {
      if (!containsForbiddenChars(c)) {
        filteredText += c;
      }
    }
  } else {
    filteredText = currentText; // If special characters are allowed, keep the
                                // original text
  }

  // Update the text in the entry if it was filtered
  if (filteredText != currentText) {
    Glib::signal_timeout().connect_once(
        [this, filteredText]() {
          setText(filteredText);
          m_Entry.set_position(filteredText.length()); // Move cursor to the end
        },
        0);
  }

  // signalTextChanged.emit(m_Entry.get_text());
}
// TODO: use key press event in another class
void Input::onKeyPressEvent() {
  // if (event->get_keyval() == GDK_KEY_Return) {
  signalEnterPressed.emit(m_Entry.get_text());
  // }
}
void Input::connectSignals() {
  // Connect Entry widget signals
  m_Entry.signal_changed().connect(sigc::mem_fun(*this, &Input::onTextChange));
  m_Entry.signal_activate().connect(
      sigc::mem_fun(*this, &Input::onKeyPressEvent));
}