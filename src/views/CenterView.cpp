#include "CenterView.hpp"

CenterView::CenterView(CategoryView *categoryView)
    : categoryView(categoryView) {

  // Set the widget name for CSS identification
  set_name("center-view");

  // Some default screens for Center Category Views
  add(*categoryView, "all", "All files");
  add(*categoryView, "trash", "Trash");
  add(*categoryView, "uncategorized", "Uncategorized");
  add(*categoryView, "tags", "Tags");
  add(*categoryView, "untagged", "Untagged");
  // Additional initialization code can go here
}

CenterView::~CenterView() {}