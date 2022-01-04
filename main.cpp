//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/2/22
//
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "src/contact.hpp"
#include "src/contact_manager.hpp"
#include "src/mycontact.hpp"

#define print(x) std::cout << x << std::endl

void to_mcsv(const std::vector<Contact> &contact_ls, const std::string &save_fp) {
  std::ofstream file(save_fp);

  file << contact_ls.begin()->get_mcsv_header() << std::endl;
  for (int i = 0; i < contact_ls.size(); i++) {
    if (i != contact_ls.size() - 1) {
      file << contact_ls[i].to_mcsv_str() << std::endl;
    } else {
      file << contact_ls[i].to_mcsv_str();
    }
  }

  file.close();
}

std::vector<Contact> to_contact_ls(const std::string &mcsv_fp) {
  std::vector<Contact> result;

  std::ifstream file(mcsv_fp);
  std::string line;
  getline(file, line, '\n'); // skip header
  while (file.good()) {
    getline(file, line, '\n');
//    std::cout << "Line: " << line << std::endl;
    result.emplace_back(line);
  }

  for (Contact c: result) {
    c.print_info();
    std::cout << "\n";
  }

  return result;
}

int main() {
  ContactManager ct_mgr;
  MyContact mc(ct_mgr);
  mc.launch();

  return 0;
}
