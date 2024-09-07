#include "CenterView.hpp"
#include "gtkmm/object.h"

CenterView::CenterView(Gtk::Window &parentWindow, CategoryView *categoryView)
    : categoryView(categoryView), parentWindow(parentWindow) {

  // Set the widget name for CSS identification
  set_name("center-view");
  auto allFiles = Gtk::make_managed<CategoryView>(parentWindow, "all");
  add(*allFiles, "all", "Category");

  auto trash = Gtk::make_managed<CategoryView>(parentWindow, "trash");
  add(*trash, "trash", "Category");

  auto uncategorized =
      Gtk::make_managed<CategoryView>(parentWindow, "uncategorized");
  add(*uncategorized, "uncategorized", "Category");

  auto untagged = Gtk::make_managed<CategoryView>(parentWindow, "untagged");
  add(*untagged, "untagged", "Category");

  auto tags = Gtk::make_managed<CategoryView>(parentWindow, "tags");
  add(*tags, "tags", "Category");
  // set_size_request();
  // set_halign(Gtk::Align::START);
  // set_valign(Gtk::Align::START);

  // set_vexpand();
  // set_hexpand();
  // Additional initialization code can go here
}

CenterView::~CenterView() {}