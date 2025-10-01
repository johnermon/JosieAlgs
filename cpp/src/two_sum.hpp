#pragma once

#import <ranges>
#import <span>
#import <unordered_map>
#import <utility>

using std::pair;
using std::span;
using std::unordered_map;
using std::views::iota;
using std::views::zip;

inline pair<size_t, size_t> two_sum(int target, span<int> input) {
  unordered_map<int, size_t> numbers;
  for (auto [i, curr] : zip(iota((size_t){0}), input)) {
    int complement = target - curr;
    auto complement_index = numbers.find(curr);
    if (complement_index != numbers.end()) {
      return {complement_index->second, i};
    }
    numbers[curr] = i;
  }
  return {0, 0};
}
