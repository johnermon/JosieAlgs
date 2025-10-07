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

typedef enum { Red, White, Blue } Color;

class DutchFlagPrinter {
private:
  size_t column;

public:
  DutchFlagPrinter(span<Color> data) { reset(data); }

  void reset(span<Color> data) {
    column = 0;
    for (int i = 0; i < data.size(); i++) {
      cout << "\n";
    }
  }

  void print_line(span<Color> data) {
    cout << "\033[" << data.size() << "A";
    cout << "\n\033[" << 2 * column << "C";
    for (int color : data) {
      switch (color) {
      case Red:
        cout << "\033[48;2;173;29;37m  \033[B\033[2D";
        break;
      case White:
        cout << "\033[48;2;255;255;255m  \033[B\033[2D";
        break;
      case Blue:
        cout << "\033[48;2;30;71;133m  \033[B\033[2D";
        break;
      }
    }
    column++;
    cout << "\033[0m";
  }

  void print_flag(span<Color> data) {
    reset(data);
    for (size_t i = 0; i <= (3 * data.size() / 2); i++) {
      print_line(data);
    }
  }
};

inline void sort_dutch_flag(span<Color> input) {
  size_t begin = 0;
  size_t end = input.size() - 1;
  size_t curr = 0;

  // dutch flag printer class prints dutch flag
  auto flag_printer = DutchFlagPrinter(input);
  while (curr < end) {

    flag_printer.print_line(input);

    switch (input[curr]) {
    case White:
      curr++;
      break;
    case Blue:
      swap(input[curr], input[end]);
      end--;
      break;
    case Red:
      swap(input[curr], input[begin]);
      begin++;
      break;
    }
    sleep_for(100ms);
  }

  cout << "\n\n\033[1mGOD BLESS THE DUTCH \033[0m\n";
  flag_printer.print_flag(input);
  cout << "\n";
}
