//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <sys/stat.h>
#include <iostream>
#include <filesystem>
#include "mycontact.hpp"
#define print(x) std::cout << x << std::endl

MyContact::MyContact() {
  if(find_contact_file())
    print("load csv!");
}

MyContact::MyContact(std::string &contact_file_path) {

}

MyContact::~MyContact() {

}

bool MyContact::find_data_dir() {
  struct stat info;
  return stat(kDataDir.c_str(), &info) == 0 && info.st_mode & S_IFDIR;
}

bool MyContact::find_contact_file() {
  if (find_data_dir() == 0) {
    mkdir(kDataDir.c_str(), 0777);
    return false;
  }

  struct stat buffer;
  if(stat(kContactFilePath.c_str(), &buffer) != 0) {
    return false;
  }

  return true;
}
