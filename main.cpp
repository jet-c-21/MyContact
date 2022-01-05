//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/2/22
//
#include <iostream>

#include "src/contact.hpp"
#include "src/contact_manager.hpp"
#include "src/mycontact.hpp"

#define print(x) std::cout << x << std::endl

int main() {
  ContactManager ct_mgr;
  MyContact mc(ct_mgr);
  mc.launch();

  return 0;
}
