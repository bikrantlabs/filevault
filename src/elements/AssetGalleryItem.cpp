#include "AssetGalleryItem.hpp"
#include "gtkmm/enums.h"

AssetGalleryItem::AssetGalleryItem(const AssetModel &asset)
    : Gtk::Box(Gtk::Orientation::VERTICAL) {
  // Load the icon from the file type or use a default one
  set_name("gallery-item");
  icon.set(asset.type == "IMAGE" ? asset.filePath : "default-icon.png");
  icon.set_pixel_size(128); // Set size for the icon

  set_size_request(100, 100);
  // Set the file name
  name.set_text("A");
  // name.set_max_width_chars(10); // Limit the length of the label
  name.set_ellipsize(Pango::EllipsizeMode::END);

  // Add icon and name to the Box
  wrapper.append(icon);
  wrapper.set_orientation(Gtk::Orientation::VERTICAL);
  wrapper.set_hexpand(false);
  wrapper.set_vexpand(false);
  wrapper.set_size_request(100, 100);
  wrapper.set_name("gallery-item-wrapper");
  append(wrapper);
}
