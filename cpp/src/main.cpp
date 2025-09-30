// header files containing my functions
#include "longest_nonrepeating_substring.hpp"
#include "two_sum.hpp"
#include "valid_intersecting_brackets.hpp"
// library imports
#include <array>
#include <print>
#include <string_view>

using std::array;
using std::println;
using std::string_view;

int main() {
  array numbers = {1, 2, 5, 7, 4, 5, 0, 49, 29, 19};
  auto [first, second] = two_sum(10, (span<int>)numbers);
  println("The indexes of sum are {} and {}\n", first, second);
  // creates new input string
  string_view input =
      "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;"
      "dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";

  // returns longest nonrepeating substring and store
  string_view out = longest_nonrepeating_substring(input);
  println("longest substring is:\n{}\n", out);
  array strings = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};

  for (string_view string : strings) {

    if (valid_intersecting_brackets(string)) {
      println("{} is a valid input", string);
    } else {
      println("{} is a invalid input", string);
    }
  }
}
