// #include "gtkmm/button.h"
// #include <gtkmm.h>

// class MyWindow : public Gtk::Window {
// public:
//   MyWindow();

// private:
//   // Main containers
//   Gtk::Box mainBox{Gtk::Orientation::HORIZONTAL};
//   Gtk::Box sidebar{Gtk::Orientation::VERTICAL};
//   Gtk::Box rightbar{Gtk::Orientation::VERTICAL};
//   Gtk::Stack mainView;

//   // Sidebar labels
//   Gtk::Button Button1{"Screen 1"};
//   Gtk::Button Button2{"Screen 2"};
//   Gtk::Button Button3{"Screen 3"};

//   // Screens
//   Gtk::Label screen1{"This is Screen 1"};
//   Gtk::Label screen2{"This is Screen 2"};
//   Gtk::Label screen3{"This is Screen 3"};

//   void on_label_clicked(const Glib::ustring &screenName);
// };

// MyWindow::MyWindow() {
//   set_title("Sidebar Navigation Example");
//   set_default_size(800, 600);

//   // Setup main containers
//   mainBox.set_expand(true);
//   mainView.set_expand(true);

//   // Add labels to sidebar
//   sidebar.set_margin(10);
//   sidebar.append(Button1);
//   sidebar.append(Button2);
//   sidebar.append(Button3);

//   // Set cursor as pointer for labels and connect signals
//   Button1.get_style_context()->add_class("label-clickable");
//   Button2.get_style_context()->add_class("label-clickable");
//   Button3.get_style_context()->add_class("label-clickable");

//   Button1.signal_clicked().connect([this]() {
//     on_label_clicked("screen1"); // Pass the category ID
//   });

//   Button2.signal_clicked().connect([this]() {
//     on_label_clicked("screen2"); // Pass the category ID
//   });

//   Button3.signal_clicked().connect([this]() {
//     on_label_clicked("screen3"); // Pass the category ID
//   });

//   // Add screens to the stack
//   mainView.add(screen1, "screen1", "Screen 1");
//   mainView.add(screen2, "screen2", "Screen 2");
//   mainView.add(screen3, "screen3", "Screen 3");

//   // Show the first screen by default
//   mainView.set_visible_child("screen1");

//   // Add elements to the main layout
//   mainBox.append(sidebar);  // Add sidebar on the left
//   mainBox.append(mainView); // Add the center main view
//   mainBox.append(rightbar); // Add rightbar on the right

//   set_child(mainBox); // Set the main layout as the window child
// }

// void MyWindow::on_label_clicked(const Glib::ustring &screenName) {
//   mainView.set_visible_child(screenName);
// }

// int main(int argc, char *argv[]) {
//   auto app = Gtk::Application::create("org.gtkmm.example");

//   MyWindow window;
//   return app->make_window_and_run<MyWindow>(argc, argv);
// }
#include "Application.hpp"

int main(int argc, char *argv[]) {
  auto app = std::make_unique<Application>();
  return app->run(argc, argv);
}