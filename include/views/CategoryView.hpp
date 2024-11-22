#pragma once

#include "AssetGalleryView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/filedialog.h"
#include "gtkmm/grid.h"
#include "gtkmm/label.h"
#include <string>

class CategoryView : public Gtk::Box {
public:
  CategoryView(Gtk::Window &parentWindow, const std::string categoryId);

protected:
  void onBrowseFilesButtonClicked();
  void onBrowseFilesFinish(const Glib::RefPtr<Gio::AsyncResult> &result,
                           const Glib::RefPtr<Gtk::FileDialog> &dialog);

private:
  std::string categoryId;
  Gtk::Label categoryViewLabel;
  Gtk::Grid wrapperBox;
  Gtk::Grid emptyWrapperBox;
  Gtk::Window &parentWindow;
  Gtk::Button browseFilesButton;
};