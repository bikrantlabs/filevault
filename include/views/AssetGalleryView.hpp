#pragma once
#include "AssetModel.hpp"
#include <gtkmm/flowbox.h>
#include <gtkmm/scrolledwindow.h>

class AssetGalleryView : public Gtk::ScrolledWindow {
public:
  AssetGalleryView(const std::vector<AssetModel> &assets);

private:
  Gtk::FlowBox flowBox;
};
