//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//

#ifndef MYCONTACT_SRC_MYCONTACT_HPP_
#define MYCONTACT_SRC_MYCONTACT_HPP_

#include <string>
#include <vector>
#include "contact.hpp"

class MyContact {
 private:
  const std::string kDataDir = "data";
  const std::string kContactFilePath = kDataDir + "/contacts.mcsv";
  std::vector<Contact> contact_ls;

 public:
  MyContact();
  MyContact(std::string &contact_file_path);
  ~MyContact();

 private:
  bool find_data_dir();
  bool find_contact_file();
};

#endif //MYCONTACT_SRC_MYCONTACT_HPP_
