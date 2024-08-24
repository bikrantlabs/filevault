#include "DirectoryDialog.hpp"

DirectoryDialog::DirectoryDialog(Gtk::Window &parent)
    : Gtk::FileChooserDialog(parent, "Select a Directory",
                             Gtk::FileChooser::Action::SELECT_FOLDER) {
  add_button("_Cancel", Gtk::ResponseType::CANCEL);
  add_button("_Open", Gtk::ResponseType::OK);
}
