#pragma once

#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include <string>
class CategoryView : public Gtk::Box {
public:
  CategoryView(const std::string categoryId);

private:
  std::string categoryId;
  Gtk::Label categoryViewLabel;
};