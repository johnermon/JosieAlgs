#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <span>
#include <stdexcept>
#include <thread>

using std::cout;
using std::span;
using std::swap;
using std::chrono::microseconds;
using std::this_thread::sleep_for;

using namespace std::chrono_literals;

typedef enum { Red, White, Blue, count } Color;

inline Color random_color() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0,
                                          static_cast<int>(Color::count) - 1);
  return static_cast<Color>(dist(gen));
}

class DutchFlagPrinter {
private:
  size_t column;

public:
  DutchFlagPrinter(span<Color> data) { reset(data); }

  void reset(span<Color> data) {
    column = 0;
    for (int i = 0; i <= data.size(); i++) {
      cout << "\n";
    }
    cout << "\033[?25l";
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
    cout << "\033[0m" << std::flush;
  }

  static void del_line(span<Color> data, size_t column) {
    cout << "\033[" << data.size() << "A";
    cout << "\n\033[" << 2 * column << "C";
    for (int i = 0; i < data.size(); i++) {
      cout << "  \033[B\033[2D" << std::flush;
    }
  }

  void print_line(span<Color> data) {
    write_line(data, column);
    column++;
  }

  void print_flag_animation(span<Color> data) {
    size_t start = column;
    size_t max = 3 * data.size() / 2;
    auto sleep_time = microseconds{500000} / data.size();

    while (column <= max) {
      print_line(data);
      sleep_for(sleep_time);
    }

    column = start;
    while (column > 0) {
      column--;
      write_line(data, column);
      sleep_for(sleep_time);
    }
  }
  ~DutchFlagPrinter() { cout << "\033[?25h"; }
};

inline void sort_dutch_flag(span<Color> input) {
  microseconds sleep_time = microseconds{1500000} / input.size();
  size_t begin = 0;
  size_t end = input.size() - 1;
  size_t curr = 0;

  // dutch flag printer class prints dutch flag
  auto flag_printer = DutchFlagPrinter(input);
  while (curr <= end) {

    flag_printer.print_line(input);

    switch (input[curr]) {
    case White:
      while (input[curr] == White) {
        curr++;
      }
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

    sleep_for(sleep_time);
  }

  flag_printer.print_flag_animation(input);
  cout << "\n\n\033[1mGOD BLESS THE DUTCH \033[0m\n";
  sleep_for(1500ms);
}
