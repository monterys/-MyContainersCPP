#ifndef MY_CONTAINERS_MY_QUEUE_H
#define MY_CONTAINERS_MY_QUEUE_H

#include "my_list.h"

namespace mycontainers {

template <class T>
class MyQueue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  MyQueue() : c_() {}
  MyQueue(std::initializer_list<value_type> const &items) : c_(items) {}
  MyQueue(const MyQueue &s) : c_(s.c_) {}
  MyQueue(MyQueue &&s) noexcept : c_(std::move(s.c_)) {}
  ~MyQueue() {}

  MyQueue &operator=(const MyQueue &s) {
    c_ = s.c_;
    return *this;
  }

  MyQueue &operator=(MyQueue &&s) noexcept {
    while (!empty()) {
      pop();
    }
    std::swap(c_, s.c_);
    return *this;
  }

  const_reference front() const { return c_.front(); }
  const_reference back() const { return c_.back(); }

  bool empty() const noexcept { return c_.empty(); }
  size_type size() const noexcept { return c_.size(); }

  void push(const_reference value) { c_.push_back(value); }
  void pop() {
    if (!c_.empty()) c_.pop_front();
  }
  void swap(MyQueue &other) { std::swap(c_, other.c_); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    c_.insert_many_back(args...);
  }

 private:
  mycontainers::list<value_type> c_;
};

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_QUEUE_H