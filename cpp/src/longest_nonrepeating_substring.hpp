#pragma once

#include <array>
#include <optional>
#include <ranges>
#include <string_view>

using std::array;
using std::get;
using std::string_view;
using std::views::iota;
using std::views::zip;

inline string_view longest_nonrepeating_substring(string_view input) {
  // initializes variables start and end for start and end of longest substring
  size_t longest_start = 0;
  size_t longest_end = 0;
  size_t curr_start = 0; // Start of current substring
  // creates array of optional size_t and fills with nullopt
  array<std::optional<size_t>, 128> char_indexes;
  char_indexes.fill(std::nullopt);

  // iterates through the input string and yields an iterated value and the char
  // at the current index, uses curr to get a reference to the last instance
  for (auto [i, curr] : zip(iota(size_t{0}), input)) {
    auto &char_index = char_indexes[(unsigned char)curr];

    // checks to make sure that the current index has if so that value is later
    // than the index of the start of the current substring
    if (char_index.has_value() && char_index > curr_start) {

      // if the lenth of the current substring is longer than the length of the
      // larges substring then set
      if (i - curr_start > longest_end - longest_start) {
        longest_start = curr_start;
        longest_end = i;
      }
      curr_start = i; // sets the current start to be equal to i
    }

    char_index = i; // Updates char index array with current index
  }

  return input.substr(longest_start, longest_end);
}
