#include "MainScreen.hpp"
#include "RightbarView.hpp"
#include "SidebarView.hpp"
#include "gtkmm/object.h"
#include <gtkmm/box.h>

MainScreen::MainScreen(Gtk::Window &parentWindow, CategoryView *categoryView,
                       CreateVault &createVaultView)
    : parentWindow(parentWindow), createVaultView(createVaultView),
      sidebar(parentWindow, &centerBox, createVaultView),
      centerBox(parentWindow, categoryView), rightbar() {

  parent.set_orientation(Gtk::Orientation::HORIZONTAL);
  auto _categoryView = Gtk::make_managed<CategoryView>(parentWindow, "all");
  // Set Widths
  sidebar.set_size_request(256, -1); // 20% of the window width for the sidebar
  centerBox.set_size_request(
      768, -1); // 60% of the window width for the main content
  rightbar.set_size_request(256, -1);

  // Only allow centerBox to expand
  centerBox.set_expand(true);
  sidebar.set_expand(false);
  rightbar.set_expand(false);
  // Append views inside parent
  parent.append(sidebar);
  parent.append(centerBox);
  parent.append(rightbar);

  // Set default screen to all(all-files)
  centerBox.set_visible_child("all");
  // Append parent itself into mainscreen
  append(parent);
}
MainScreen::~MainScreen() {}
