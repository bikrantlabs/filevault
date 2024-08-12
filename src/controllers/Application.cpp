#include "Application.hpp"
#include "MainWindow.hpp"

Application::Application() : Gtk::Application("com.example.yourdamapp") {}

void Application::on_activate() {
  auto win = new MainWindow();
  add_window(*win);
  win->present();
}
