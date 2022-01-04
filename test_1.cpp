#include <string>
#include <iostream>
#include <map>

using namespace std;

enum class state_t {
  unknown,
  off,
  on,
  fault
};

typedef std::map<state_t, std::string> statemap_t;

statemap_t state = {
    {state_t::unknown, "unknown"},
    {state_t::off, "off"},
    {state_t::on, "on"},
    {state_t::fault, "fault"}
};

void allowStateChange(const state_t localState, const state_t globalState, const state_t newState) {
  //Some code to verify if the state transition is allowed.
  std::cout
      << "Device Local State:"
      << state.find(localState)->second
      << ", Device Global State:"
      << state.find(globalState)->second
      << ", Device New State:"
      << state.find(newState)->second
      << std::endl;
}

int main() {
  allowStateChange(state_t::on, state_t::off, state_t::fault);
  return 0;
}