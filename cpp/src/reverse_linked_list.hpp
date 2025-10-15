#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <utility>

template <typename T> class JosieLinkedList {

private:
  class JosieLinkedListSegment {
  public:
    JosieLinkedListSegment *ptr;
    T data;

    static JosieLinkedListSegment *create(T &&element) {
      auto ptr =
          (JosieLinkedListSegment *)malloc(sizeof(JosieLinkedListSegment));

      if (ptr == nullptr) {
        throw std::runtime_error("Failed to malloc for segment");
      }

      ptr->ptr = nullptr;
      ptr->data = std::move(element);

      return ptr;
    }
  };

  class JosieLinkedListIter {
    JosieLinkedListSegment *current;

  public:
    explicit JosieLinkedListIter(JosieLinkedListSegment *start)
        : current(start) {}
    T &operator*() const { return current->data; }
    JosieLinkedListIter &operator++() {
      current = current->ptr;
      return *this;
    }

    bool operator!=(const JosieLinkedListIter &other) {
      return current != other.current;
    }
  };

  JosieLinkedListSegment *list;
  JosieLinkedListSegment *tail_pointer;

  size_t length;

public:
  JosieLinkedList() : list(nullptr), tail_pointer(nullptr), length(0) {}

  void push_back(T element) {
    auto segment = JosieLinkedListSegment::create(std::move(element));
    length++;
    if (list == nullptr) {
      list = segment;
      tail_pointer = segment;
      return;
    }
    tail_pointer->ptr = segment;
    tail_pointer = segment;
  }

  void push_front(T element) {
    auto segment = JosieLinkedListSegment::create(std::move(element));
    length++;
    segment->ptr = list;
    list = segment;
  }

  void reverse() {
    if (list != nullptr) {
      auto original = list->ptr;
      auto reversed = list;
      reversed->ptr = nullptr;
      tail_pointer = reversed;
      while (original != nullptr) {
        auto next = original->ptr;
        original->ptr = reversed;
        reversed = original;
        original = next;
      }
      list = reversed;
    }
  }

  size_t len() { return length; }

  bool is_empty() { return 0 == length; }

  JosieLinkedListIter begin() { return JosieLinkedListIter(list); }

  JosieLinkedListIter end() { return JosieLinkedListIter(nullptr); }

  ~JosieLinkedList() {
    auto next = list;
    while (next != nullptr) {
      next->data.~T();
      auto to_dealloc = next;
      next = next->ptr;
      free(to_dealloc);
    }
  }
};
