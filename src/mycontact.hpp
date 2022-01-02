//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <string>
#include <vector>
#include "contact.hpp"

class MyContact {
 private:
  std::string m_data_fp;
  std::vector<Contact> contact_data;

 public:
  MyContact();
  MyContact(std::string &contact_file_path);
  ~MyContact();

 private:
  bool find_data_dir();
  bool find_contact_file();
};


