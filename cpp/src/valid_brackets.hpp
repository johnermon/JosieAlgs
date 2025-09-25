#pragma once
#include <optional>
#include <string_view>
#include <vector>
using std::optional;
using std::string_view;
using std::vector;

inline bool valid_brackets(string_view input) {
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
    for (size_t i = stack.size(); i-- > 0;) {
      if (stack[i] == open) {
        stack.erase(stack.begin() + i);
        goto continue_outer;
      }
    }
    return false;
  continue_outer:;
  }
  return stack.empty();
}
