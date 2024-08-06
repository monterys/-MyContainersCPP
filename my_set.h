#ifndef __MY_CONTAINERS_MY_SET_H__
#define __MY_CONTAINERS_MY_SET_H__

#include "my_tree.h"

namespace mycontainers {

template <class Key>
class MySet {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = typename BinaryTree<Key, Key>::const_iterator;
  using size_type = size_t;

  MySet() : tree_() {}
  MySet(std::initializer_list<value_type> &items) {
    for (auto &item : items) {
      tree_.insertToTree(item);
    }
  }
  MySet(value_type &item) { tree_.insertToTree(item); }
  MySet(const MySet &s) : tree_(s.tree_) {}
  MySet(MySet &&s) noexcept : tree_(std::move(s.tree_)) {}
  ~MySet() = default;

  MySet &operator=(const MySet &s) {
    MySet tmp(s);
    std::swap(tree_, tmp.tree_);
    return *this;
  }

  MySet &operator=(MySet &&s) noexcept {
    std::swap(tree_, s.tree_);
    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  bool empty() const noexcept { return (begin() == end()); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() { tree_.clear(); }
  std::pair<iterator, bool> insert(const_reference value) {
    return tree_.insertToTree(value);
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(MySet &other) { std::swap(tree_, other.tree_); }
  void merge(MySet &other) { tree_.merge(other.tree_); }

  iterator find(const key_type &key) const noexcept { return tree_.find(key); }
  bool contains(const key_type &key) const noexcept {
    return tree_.contains(key);
  }

  template <typename... Args>
  mycontainers::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    mycontainers::vector<std::pair<iterator, bool>> result;
    (result.push_back(tree_.insertToTree(args)), ...);
    return result;
  }

 private:
  BinaryTree<key_type, value_type> tree_;
};  // class MySet

}  // namespace mycontainers

#endif  // __MY_CONTAINERS_MY_SET_H__
