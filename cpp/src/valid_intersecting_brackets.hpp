#pragma once

#include <optional>
#include <ranges>
#include <string_view>
#include <vector>

using std::optional;
using std::string_view;
using std::vector;
using std::views::iota;
using std::views::zip;

inline bool valid_intersecting_brackets(string_view input) {
  vector<char> stack;
  for (char curr : input) {
    if (curr == '(' || curr == '{' || curr == '[' || curr == '<') {
      stack.push_back(curr);
      continue;
    }
    char open;
    switch (curr) {
    case ')':
      open = '(';
      break;
    case '}':
      open = '{';
      break;
    case ']':
      open = '[';
      break;
    case '>':
      open = '<';
      break;
    default:
      continue;
    }
    for (auto [i, curr] : zip(iota(0), stack)) {
      if (curr == open) {
        stack.erase(stack.begin() + i);
        goto continue_outer;
      }
    }
    return false;
  continue_outer:;
  }
  return stack.empty();
}
