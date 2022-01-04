#include <vector>
#include <iostream>

int main() {
  std::vector<int> original_ls = {1, 2, 3};
  std::vector<int> new_ls = {4, 5, 6};

  // reserve() is optional - just to improve performance
  original_ls.reserve(original_ls.size() + distance(new_ls.begin(), new_ls.end()));
  original_ls.insert(original_ls.end(), new_ls.begin(), new_ls.end());

  for (int i: original_ls) {
    std::cout << i << std::endl;
  }
  std::cout << "\n";

  original_ls.erase(original_ls.begin() + 1);
  for (int i: original_ls) {
    std::cout << i << std::endl;
  }
}
