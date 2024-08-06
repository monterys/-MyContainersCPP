#ifndef MY_CONTAINERS_MY_MAP_H
#define MY_CONTAINERS_MY_MAP_H

#include "my_tree.h"

namespace mycontainers {

template <class Key, class T>
class MyMap {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = typename BinaryTree<Key, Key>::const_iterator;
  using size_type = size_t;

  MyMap() : tree_() {}

  MyMap(std::initializer_list<value_type> const &items) {
    for (auto &[key, value] : items) {
      tree_.insertToTree(key, value, false);
    }
  }

  MyMap(const MyMap &m) : tree_(m.tree_) {}
  MyMap(MyMap &&s) noexcept : tree_(std::move(s.tree_)) {}
  ~MyMap() = default;

  MyMap &operator=(const MyMap &s) {
    MyMap tmp(s);
    std::swap(tree_, tmp.tree_);
    return *this;
  }

  MyMap &operator=(MyMap &&s) noexcept {
    std::swap(tree_, s.tree_);
    return *this;
  }

  mapped_type &at(const Key &key) const;

  mapped_type &operator[](const Key &key);

  iterator begin() const noexcept { return tree_.begin(); }
  iterator end() const noexcept { return tree_.end(); }

  bool empty() const noexcept { return (begin() == end()); }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insertToTree(value.first, value.second, false);
  }

  std::pair<iterator, bool> insert(const Key &key, const mapped_type &obj) {
    return tree_.insertToTree(key, obj, false);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const mapped_type &obj) {
    return tree_.insertOrAssign(key, obj);
  }

  void erase(iterator pos) { tree_.erase(pos); }
  void swap(MyMap &other) { std::swap(tree_, other.tree_); }
  void merge(MyMap &other) { tree_.merge(other.tree_); }

  iterator find(const Key &key) const { return tree_.find(key); }

  bool contains(const Key &key) const noexcept { return tree_.contains(key); }

  template <typename... Args>
  mycontainers::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    mycontainers::vector<std::pair<iterator, bool>> result;
    (result.push_back(tree_.insertToTree(args, false)), ...);
    return result;
  }

 private:
  BinaryTree<key_type, mapped_type> tree_;
};

template <class Key, class T>
T &MyMap<Key, T>::at(const Key &key) const {
  static T value;

  if (tree_.contains(key)) {
    value = *(tree_.find(key));
  } else {
    throw std::out_of_range("mycontainers::MyMap::at");
  }

  return value;
}

template <class Key, class T>
T &MyMap<Key, T>::operator[](const Key &key) {
  static T value;

  if (tree_.contains(key)) {
    value = *(tree_.find(key));
  } else {
    value = (tree_.insertToTree(key, T(), false).first)->second;
  }

  return value;
}

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_MAP_H
