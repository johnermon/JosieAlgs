#pragma once

#include <cstddef>
#include <exception>
#include <iostream>
#include <random>
#include <span>
#include <stdexcept>
#include <thread>
#include <utility>

using std::cout;
using std::span;
using std::swap;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

typedef enum { Red, White, Blue, count } Color;

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

  static void write_line(span<Color> data, size_t column) {
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
    cout << "\033[0m";
  }

  void print_line(span<Color> data) {
    write_line(data, column);
    column++;
  }

  void reverse_print_line(span<Color> data) {
    column--;
    write_line(data, column);
  }

  void print_flag_animation(span<Color> data) {
    size_t start = column;

    while (column <= 3 * data.size() / 2) {
      print_line(data);
      sleep_for(50ms);
    }

    column = start;
    while (column > 0) {
      reverse_print_line(data);
      sleep_for(50ms);
    }
  }
};

inline Color random_color() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0,
                                          static_cast<int>(Color::count) - 1);
  return static_cast<Color>(dist(gen));
}

inline void sort_dutch_flag(span<Color> input) {
  size_t begin = 0;
  size_t end = input.size() - 1;
  size_t curr = 0;

  // dutch flag printer class prints dutch flag
  auto flag_printer = DutchFlagPrinter(input);
  while (curr <= end) {

    flag_printer.print_line(input);

    switch (input[curr]) {
    case White:
      curr++;
      break;

    case Blue:
      swap(input[curr], input[end]);
      while (input[end] == Blue) {
        end--;
      }
      break;

    case Red:
      swap(input[curr], input[begin]);
      while (input[begin] == Red) {
        begin++;
      }
      curr = begin;
      break;
    case count:
      throw std::runtime_error("somehow count enum made it into the vector");
    }
    sleep_for(50ms);
  }

  flag_printer.print_flag_animation(input);
  cout << "\n\n\033[1mGOD BLESS THE DUTCH \033[0m\n";
  sleep_for(1500ms);
}
