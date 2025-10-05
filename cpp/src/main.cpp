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
  println("Hello from C++!");

  array numbers = {1, 2, 5, 7, 4, 5, 0, 49, 29, 19};
  auto sum = two_sum(10, (span<int>)numbers);
  if (sum.has_value()) {
    println("the indexes of sum are {} and {}", sum->first, sum->second);
  } else {
    println("there is no pair of numbers that equal to target");
  }

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
