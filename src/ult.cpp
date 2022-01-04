//
// Author: Jet Chien
// GitHub: https://github.com/jet-c-21
// Create Date: 1/2/22
//
#include "ult.hpp"

namespace g_ult {

std::vector<std::string> split_str(const std::string &s, const std::string &d) {
  std::vector<std::string> result;

  int start = 0;
  int end = s.find(d);
  std::string token;
  while (end != -1) {
    token = s.substr(start, end - start);
    result.push_back(token);
    start = end + (int) d.size();
    end = s.find(d, start);
  }
  token = s.substr(start, end - start);
  result.push_back(token);

  return result;
}

}