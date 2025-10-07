#pragma once

#include <cstddef>
#include <iostream>
#include <span>
#include <string>
#include <thread>
#include <utility>

using std::cout;
using std::span;
using std::swap;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

typedef enum { red, white, blue } color;

class dutch_flag_printer {
private:
  size_t column;
  span<color> data;

public:
  dutch_flag_printer(span<color> data) : data(data) { reset(); }

  void reset() {
    column = 0;
    for (int i = 0; i < data.size(); i++) {
      cout << "\n";
    }
  }

  void print_line() {
    cout << "\033[" << data.size() - 1 << "A" << "\n";
    cout << "\033[" << 2 * column << "C";
    for (int i : data) {
      switch (i) {
      case red:
        cout << "\033[48;2;173;29;37m  \033[B\033[2D";
        break;
      case white:
        cout << "\033[48;2;255;255;255m  \033[B\033[2D";
        break;
      case blue:
        cout << "\033[48;2;30;71;133m  \033[B\033[2D";
        break;
      }
    }
    cout << "\033[0m";
    column++;
  }
};

inline void sort_dutch_flag(span<color> input) {
  size_t begin = 0;
  size_t end = input.size() - 1;
  size_t curr = 0;
  size_t column = 0;

  // dutch flag printer class prints dutch flag
  auto flag_printer = dutch_flag_printer(input);
  while (curr < end) {

    flag_printer.print_line();

    switch (input[curr]) {
    case white:
      curr++;
      break;
    case blue:
      swap(input[curr], input[end]);
      end--;
      break;
    case red:
      swap(input[curr], input[begin]);
      begin++;
      break;
    }
    sleep_for(100ms);
  }

  cout << "\n\n\033[1mGOD BLESS THE DUTCH \033[0m\n";
  flag_printer.reset();
  for (size_t i = 0; i <= (3 * input.size() / 2); i++) {
    flag_printer.print_line();
  }

  cout << "\n";
}
