#pragma once
#include <gtkmm.h>

class DirectoryDialog : public Gtk::FileChooserDialog {
public:
  DirectoryDialog(Gtk::Window &parent);
  virtual ~DirectoryDialog() = default;
  // Connect to the selection_changed signal
};
