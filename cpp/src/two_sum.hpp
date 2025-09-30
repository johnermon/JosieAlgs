#pragma once

#include <cstddef>
#import <iostream>
#import <ranges>
#import <span>
#import <unordered_map>
#import <utility>

using std::cout;
using std::pair;
using std::span;
using std::unordered_map;
using std::views::iota;
using std::views::zip;

inline pair<size_t, size_t> two_sum(int target, span<int> input) {
  unordered_map<int, size_t> numbers;
  int index_one = 0;
  int index_two = 0;
  for (auto [i, curr] : zip(iota((size_t){0}), input)) {
    int complement = target - curr;
    auto complement_index = numbers.find(curr);
    if (complement_index != numbers.end()) {
      index_one = complement_index->second;
      index_two = i;
      break;
    }
    numbers[curr] = i;
  }
  return {index_one, index_two};
}
