#pragma once

#import <optional>
#import <ranges>
#import <span>
#import <unordered_map>
#import <utility>

using std::optional;
using std::pair;
using std::span;
using std::unordered_map;
using std::views::iota;
using std::views::zip;

inline optional<pair<size_t, size_t>> two_sum(int target, span<int> input) {
  unordered_map<int, size_t> numbers;
  for (auto [i, curr] : zip(iota((size_t){0}), input)) {
    int complement = target - curr;
    auto complement_index = numbers.find(curr);
    if (complement_index != numbers.end()) {
      return std::make_pair(complement_index->second, i);
    }
    numbers[curr] = i;
  }
  return std::nullopt;
}
