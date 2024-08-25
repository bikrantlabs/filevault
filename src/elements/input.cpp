#include "input.hpp"

Input::Input() : Gtk::Box(Gtk::Orientation::VERTICAL) {
  m_Entry.set_max_length(16);
  m_Entry.signal_changed().connect(sigc::mem_fun(*this, &Input::onTextChange));
  append(m_Entry);
}

Input::~Input() {}

void Input::setText(const Glib::ustring &text) { m_Entry.set_text(text); }

Glib::ustring Input::getText() const { return m_Entry.get_text(); }

Gtk::Entry &Input::getEntry() { return m_Entry; }

void Input::setEditable(bool editable) { m_Entry.set_editable(editable); }

bool Input::isEditable() const { return m_Entry.get_editable(); }

void Input::setVisible(bool visible) { m_Entry.set_visibility(visible); }

bool Input::isVisible() const { return m_Entry.get_visibility(); }

void Input::onTextChange() { signalTextChanged.emit(m_Entry.get_text()); }
