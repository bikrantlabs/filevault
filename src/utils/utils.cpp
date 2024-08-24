#include "utils.hpp"
#include <fstream>
#include <string>
void saveUserName(const std::string &username) {
  std::ofstream file("../config.txt");
  file << username;
}

std::string loadUserName() {
  std::ifstream file("../config.txt");
  std::string username;
  if (file >> username) {
    return username;
  }
  return "";
}
