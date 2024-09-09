#include "AssetGalleryView.hpp"
#include "AssetGalleryItem.hpp"

AssetGalleryView::AssetGalleryView(const std::vector<AssetModel> &assets) {
  set_hexpand();
  set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);

  flowBox.set_selection_mode(Gtk::SelectionMode::NONE);
  flowBox.set_homogeneous(false);
  // Create a GalleryItem for each asset and add it to the FlowBox
  for (const auto &asset : assets) {
    auto item = Gtk::make_managed<AssetGalleryItem>(asset);
    flowBox.insert(*item, -1);
  }

  flowBox.set_max_children_per_line(5); // Adjust to fit your desired layout
  flowBox.set_selection_mode(Gtk::SelectionMode::NONE);
  set_child(flowBox);
}
