#pragma once
#include "AssetModel.hpp"
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/widget.h>

class AssetGalleryItem : public Gtk::Box {
public:
  AssetGalleryItem(const AssetModel &asset);

private:
  Gtk::Box wrapper;
  Gtk::Image icon;
  Gtk::Label name;
};
