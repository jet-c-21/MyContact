//
// Author: Jet Chien
// GitHub: https://github.com/jet-chien
// Create Date: 1/2/22
//
#include <iostream>
#include "src/contact.hpp"


int main() {
  Contact c1;
  c1.set_name("puff");
  c1.print_info();

  Contact c2("jet", "12345", "tw", "abc@gmail.com", "cool guy");
  c2.print_info();

  return 0;
}
