#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string_view>
#include <tuple>

using std::array;
using std::cout;
using std::get;
using std::make_tuple;
using std::nullopt;
using std::optional;
using std::string_view;
using std::tuple;

inline string_view longest_nonrepeating_substring(string_view input) {
  tuple<size_t, size_t> longest_substring_range;
  size_t curr_substring_index = 0;
  array<std::optional<size_t>, 128> char_indexes;
  char_indexes.fill(nullopt);
  ;
  for (size_t i = 0; i < input.size(); i++) {
    char curr = input[i];
    auto &char_index = char_indexes[curr];
    if (char_index.has_value() && char_index > curr_substring_index) {
      if (i - curr_substring_index >
          get<1>(longest_substring_range) - get<0>(longest_substring_range)) {
        longest_substring_range = make_tuple(curr_substring_index, i);
      }
      curr_substring_index = i;
    }
    char_index = i;
  }
  return input.substr(get<0>(longest_substring_range),
                      get<1>(longest_substring_range));
}
