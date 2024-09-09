#include "CategoryView.hpp"
#include "AssetGalleryView.hpp"
#include "CategoryModel.hpp"
#include "FileUtils.hpp"
#include "giomm/liststore.h"
#include "glibmm/ustring.h"
#include "gtkmm/button.h"
#include "gtkmm/error.h"
#include "gtkmm/filedialog.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include <iostream>
#include <vector>
CategoryView::CategoryView(Gtk::Window &parentWindow,
                           const std::string categoryId)
    : parentWindow(parentWindow), browseFilesButton("Browse Files"),
      categoryViewLabel(categoryId), categoryId(categoryId) {
  set_name("category-view");

  CategoryModel &categoryModel = CategoryModel::getInstance();
  auto assets = categoryModel.getAssetsByCategory(categoryId);
  for (auto &asset : assets) {
    std::cout << "🟢 [CategoryView.cpp:22]: " << "Asset:" << asset.name
              << std::endl;
  }
  browseFilesButton.set_cursor("pointer");
  browseFilesButton.set_hexpand(false);
  browseFilesButton.set_size_request(10, -1);
  browseFilesButton.set_vexpand(false);
  browseFilesButton.signal_clicked().connect(
      sigc::mem_fun(*this, &CategoryView::onBrowseFilesButtonClicked));
  if (assets.empty()) {

    auto lockIcon = Gtk::make_managed<Gtk::Image>("../assets/upload-icon.png");
    lockIcon->set_pixel_size(132);

    Gtk::Label label(categoryId);
    Gtk::Label label2("Start by uploading some files!");
    label.add_css_class("muted-label");
    label2.add_css_class("muted-label");
    label.set_margin_top(20);

    emptyWrapperBox.attach(*lockIcon, 0, 0, 1, 1);
    emptyWrapperBox.attach(label, 0, 1, 1, 1);
    emptyWrapperBox.attach(label2, 0, 2, 1, 1);
    emptyWrapperBox.attach(browseFilesButton, 0, 3, 1, 1);

    emptyWrapperBox.set_column_homogeneous(false);
    emptyWrapperBox.set_row_homogeneous(false);
    emptyWrapperBox.set_row_spacing(8);
    emptyWrapperBox.set_hexpand();
    emptyWrapperBox.set_vexpand();
    emptyWrapperBox.set_halign(Gtk::Align::CENTER);
    emptyWrapperBox.set_valign(Gtk::Align::CENTER);

    // emptyWrapperBox.set_name("empty-wrapper-box");

    append(emptyWrapperBox);
  } else {
    // Create and append GalleryView when assets are present
    auto assetGalleryView = Gtk::make_managed<AssetGalleryView>(assets);
    append(*assetGalleryView);
    append(browseFilesButton);
  }

  set_vexpand();
  set_hexpand();
};
void CategoryView::onBrowseFilesButtonClicked() {
  std::cout << "🟢 [CategoryView.cpp:50]: " << "Something clicked!"
            << std::endl;
  auto dialog = Gtk::FileDialog::create();
  // Add filters, so that only certain file types can be selected:
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  filters->append(filter_any);

  dialog->set_filters(filters);

  // Show the dialog and wait for a user response:
  dialog->open_multiple(
      parentWindow,
      sigc::bind(sigc::mem_fun(*this, &CategoryView::onBrowseFilesFinish),
                 dialog));
}
void CategoryView::onBrowseFilesFinish(
    const Glib::RefPtr<Gio::AsyncResult> &result,
    const Glib::RefPtr<Gtk::FileDialog> &dialog) {

  try {
    CategoryModel &categoryModel = CategoryModel::getInstance();
    auto files = dialog->open_multiple_finish(result);

    auto assets = FileUtils::convertFilesToAssetModels(files);
    categoryModel.addAssetsToCategory(assets, categoryId);

  } catch (const Gtk::DialogError &err) {
    // Can be thrown by dialog->open_finish(result).
    std::cout << "No file selected. " << err.what() << std::endl;
  } catch (const Glib::Error &err) {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}
