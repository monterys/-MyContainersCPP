#ifndef MY_CONTAINERS_MY_STACK_H
#define MY_CONTAINERS_MY_STACK_H

#include "my_list.h"

namespace mycontainers {

template <class T>
class MyStack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  MyStack() : c_() {}
  MyStack(std::initializer_list<value_type> const &items) : c_(items) {}
  MyStack(const MyStack &s) : c_(s.c_) {}
  MyStack(MyStack &&s) noexcept : c_(std::move(s.c_)) {}
  ~MyStack() {}

  MyStack &operator=(const MyStack &s) {
    c_ = s.c_;
    return *this;
  }

  MyStack &operator=(MyStack &&s) noexcept {
    while (!empty()) {
      pop();
    }
    std::swap(c_, s.c_);
    return *this;
  }

  const_reference top() const { return c_.back(); }

  bool empty() const noexcept { return c_.empty(); }
  size_type size() const noexcept { return c_.size(); }

  void push(const_reference value) { c_.push_back(value); }
  void pop() {
    if (!c_.empty()) c_.pop_back();
  }
  void swap(MyStack &other) { std::swap(c_, other.c_); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    c_.insert_many_back(args...);
  }

 private:
  mycontainers::list<value_type> c_;
};

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_STACK_H