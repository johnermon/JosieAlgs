// header files containing my functions
#include "longest_nonrepeating_substring.hpp"
#include "valid_intersecting_brackets.hpp"
// library imports
#include <array>
#include <iostream>
#include <string_view>

using std::array;
using std::cout;
using std::string_view;

int main() {
  // creates new input string
  string_view input =
      "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;"
      "dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";

  // returns longest nonrepeating substring and store
  string_view out = longest_nonrepeating_substring(input);
  cout << "\nlongest substring is:\n" << out << "\n\n";

  array strings = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};

  for (string_view string : strings) {

    if (valid_intersecting_brackets(string)) {
      cout << string << " is a valid input\n";
    }

    else {
      cout << string << " is not a valid input\n";
    }
  }
}
