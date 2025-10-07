// header files containing my functions
#include "longest_nonrepeating_substring.hpp"
#include "reverse_linked_list.hpp"
#include "sort_dutch_flag.hpp"
#include "two_sum.hpp"
#include "valid_intersecting_brackets.hpp"

// library imports
#include <array>
#include <cstddef>
#include <iostream>
#include <print>
#include <string_view>

using std::array;
using std::cout;
using std::println;
using std::string_view;

int main() {
  println("Hello from C++!\n");
  println("Reverse a linked list\n");
  println("contents");
  auto list = JoiseLinkedList<int>();
  for (int i = 0; i <= 10; i++) {
    list.push_back(i);
  }

  for (auto i : list) {
    cout << i << ", ";
  }
  cout << "\n\n";

  list.reverse();

  println("Reversed");
  for (auto i : list) {
    cout << i << ", ";
  }
  cout << "\n\n";

  println("Sort Dutch Flag");
  array scrambled_flag = {white, red,   red,  blue,  blue,  red,
                          white, white, blue, blue,  white, white,
                          red,   red,   blue, white, white};
  sort_dutch_flag((span<color>)scrambled_flag);

  println("\nTwo sum\n");
  array numbers = {1, 2, 5, 7, 4, 5, 0, 49, 29, 19};
  println("Input is: \n");
  for (auto i : numbers) {
    cout << i << ", ";
  }
  cout << "\n\n";
  auto sum = two_sum(10, (span<int>)numbers);
  if (sum.has_value()) {
    println("the indexes of sum are {} and {}\n", sum->first, sum->second);
  } else {
    println("there is no pair of numbers that equal to target\n");
  }

  println("Longest nonrepeating substring\n");
  string_view input =
      "aloikjhjasdfyhuiiouehjfgopwq;ewrdfgjwqdp[ovmwpeoirkjfvcwq;olkdjvsa;"
      "dlqwertyuiopaSDFGHJKLkgjkfs[v[vqerpokrvfg";

  println("Input is: \n{}\n", input);

  // returns longest nonrepeating substring and store
  string_view out = longest_nonrepeating_substring(input);
  println("longest substring is:\n{}\n", out);

  println("Valid intersecting Brackets\n");
  array brackets = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};

  for (string_view string : brackets) {
    if (valid_intersecting_brackets(string)) {
      println("{} is a valid input", string);
    } else {
      println("{} is a invalid input", string);
    }
  }
}
