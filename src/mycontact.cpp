//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <sys/stat.h>
#include <iostream>
#include "mycontact.hpp"
#define print(x) std::cout << x << std::endl

MyContact::MyContact() {
  find_data_dir();
}

MyContact::MyContact(std::string &contact_file_path) {

}

MyContact::~MyContact() {

}
bool MyContact::find_data_dir() {
  std::string data_dir = "data";
  struct stat info;

  return stat(data_dir.c_str(), &info) == 0 && info.st_mode & S_IFDIR;
}
