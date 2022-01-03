#include <string>
#include <iostream>
#include <iomanip>

void f(int &a) {
  int b = a;
  b++;
  std::cout << b << std::endl;
}

int main(int argc, char *argv[]) {
  int a = 1;
  std::cout << a << std::endl;
  f(a);
  std::cout << a << std::endl;
}