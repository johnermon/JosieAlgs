// header files containing my functions
#include "longest_nonrepeating_substring.hpp"
#include "valid_brackets.hpp"
// library imports
#include <array>
#include <iostream>
#include <string_view>

using std::array;
using std::cout;
using std::string_view;

int main() {
  string_view input = "aloikjhjasdfyhui "
                      "iouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;"
                      "dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";

  string_view out = longest_nonrepeating_substring(input);
  cout << out << '\n';
  array strings = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};
  for (string_view string : strings) {
    if (valid_brackets(string)) {
      cout << string << " is a valid input\n";
    } else {
      cout << string << " is not a valid input\n";
    }
  }
}
