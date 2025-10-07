#pragma once

#include <cstddef>
#include <iostream>
#include <span>
#include <thread>
#include <utility>

using std::cout;
using std::span;
using std::swap;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

typedef enum { red, white, blue } color;

inline void print_dutch_flag(span<color> input) {
  for (int i : input) {
    switch (i) {
    case red:
      cout << "\033[48;2;173;29;37m  ";
      break;
    case white:
      cout << "\033[48;2;255;255;255m  ";
      break;
    case blue:
      cout << "\033[48;2;30;71;133m  ";
      break;
    }
  }
  cout << "\033[0m" << "\n";
}

inline void sort_dutch_flag(span<color> input) {
  size_t begin = 0;
  size_t end = input.size() - 1;
  size_t curr = 0;

  while (curr < end - 1) {
    print_dutch_flag(input);

    if (input[curr] == white) {
      curr++;
    }

    if (input[curr] == blue) {
      swap(input[curr], input[end]);
      end--;
      continue;
    }

    if (input[curr] == red) {
      swap(input[curr], input[begin]);
      begin++;
    }
    sleep_for(250ms);
  }
  cout << "\n\n\033[1mGOD BLESS THE DUTCH \033[0m(this is a french flag circa "
          "the 1790s)\n";
  for (size_t i = 0; i <= 8; i++) {
    print_dutch_flag(input);
  }
}
