#include <cstddef>
#include <cstdlib>
#include <stdexcept>

template <typename T> class JosieLinkedListSegment {
public:
  JosieLinkedListSegment<T> *ptr;
  T data;

  static JosieLinkedListSegment<T> *create(T element) {
    auto segment = JosieLinkedListSegment{nullptr, element};
    auto ptr =
        (JosieLinkedListSegment<T> *)malloc(sizeof(JosieLinkedListSegment<T>));

    if (ptr == nullptr) {
      throw std::runtime_error("Failed to malloc for segment");
    }
    *ptr = segment;
    return ptr;
  }
};

template <typename T> class JoiseLinkedList {
private:
  JosieLinkedListSegment<T> *list;
  JosieLinkedListSegment<T> *tail_pointer;
  size_t len;

public:
  JoiseLinkedList() : list(nullptr), tail_pointer(nullptr), len(0) {}

  void push_back(T element) {
    auto segment = JosieLinkedListSegment<T>::create(element);
    if (list == nullptr) {
      list = segment;
      tail_pointer = segment;
      return;
    }
    len++;
    tail_pointer->ptr = segment;
    tail_pointer = segment;
  }
  void push_front(T element) {
    auto segment = JosieLinkedListSegment<T>::create(element);
    auto curr = list;
    list = segment;
    len++;
    list->ptr = curr;
  }
  void reverse() {
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
  class Iterator {
    JosieLinkedListSegment<T> *current;

  public:
    explicit Iterator(JosieLinkedListSegment<T> *start) : current(start) {}
    T &operator*() const { return current->data; }
    Iterator &operator++() {
      current = current->ptr;
      return *this;
    }

    bool operator!=(const Iterator &other) { return current != other.current; }
  };

  Iterator begin() { return Iterator(list); }

  Iterator end() { return Iterator(nullptr); }

  ~JoiseLinkedList<T>() {
    auto next = list;
    while (next != nullptr) {
      next->data.~T();
      auto to_dealloc = next;
      next = next->ptr;
      free(to_dealloc);
    }
  }
};
