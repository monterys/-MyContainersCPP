#ifndef MY_CONTAINERS_MY_MULTISET_H
#define MY_CONTAINERS_MY_MULTISET_H

#include "my_tree.h"

namespace mycontainers {

template <class Key>
class MyMultiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = typename BinaryTree<Key, Key>::const_iterator;
  using size_type = size_t;

  MyMultiset() : tree_() {}
  MyMultiset(std::initializer_list<value_type> &items) {
    for (auto &item : items) {
      tree_.insertToTree(item, item, true);
    }
  }
  MyMultiset(const MyMultiset &ms) : tree_(ms.tree_) {}
  MyMultiset(MyMultiset &&ms) noexcept : tree_(std::move(ms.tree_)) {}
  ~MyMultiset() = default;

  MyMultiset &operator=(const MyMultiset &ms) {
    MyMultiset tmp(ms);
    std::swap(tree_, tmp.tree_);
    return *this;
  }

  MyMultiset &operator=(MyMultiset &&ms) noexcept {
    std::swap(tree_, ms.tree_);
    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  bool empty() const noexcept { return (begin() == end()); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() { tree_.clear(); }
  iterator insert(const_reference value) {
    return (tree_.insertToTree(value, value, true)).first;
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(MyMultiset &other) { std::swap(tree_, other.tree_); }
  void merge(MyMultiset &other) { tree_.merge(other.tree_, true); }

  iterator find(const key_type &key) const noexcept { return tree_.find(key); }

  bool contains(const key_type &key) const noexcept {
    return tree_.contains(key);
  }

  size_type count(const Key &key) const { return tree_.count(key); }
  std::pair<iterator, iterator> equal_range(const Key &key) const {
    return tree_.equal_range(key);
  }
  iterator lower_bound(const Key &key) const { return tree_.lower_bound(key); }
  iterator upper_bound(const Key &key) const { return tree_.upper_bound(key); }

  template <typename... Args>
  mycontainers::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    mycontainers::vector<std::pair<iterator, bool>> result;
    (result.push_back(tree_.insertToTree(args, true)), ...);
    return result;
  }

 private:
  BinaryTree<key_type, value_type> tree_;
};  // class MyMultiset

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_MULTISET_H
