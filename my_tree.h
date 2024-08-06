#ifndef __MY_CONTAINERS_MY_TREE_H__
#define __MY_CONTAINERS_MY_TREE_H__

#include "my_vector.h"

namespace mycontainers {

template <class Key, class T>
class BinaryTree {
  class Node;
  class TreeIterator;
  class ConstTreeIterator;

 public:
  using key_type = Key;
  using value_type = T;
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;
  using size_type = size_t;

  BinaryTree() = default;
  BinaryTree(value_type value) : root_(new Node(value)) {}
  BinaryTree(key_type key, value_type value) : root_(new Node(key, value)) {}
  BinaryTree(const BinaryTree &other) { root_ = copyTree(other.root_); }
  BinaryTree(BinaryTree &&other) noexcept { swap(other); }
  ~BinaryTree() { clear(); }

  BinaryTree &operator=(const BinaryTree &other);
  BinaryTree &operator=(BinaryTree &&other) noexcept;

  size_t max_size() const noexcept { return size_max_; }
  size_t size() const noexcept { return nodeCount_; }
  iterator begin() const { return iterator(getMinNode(), this); }
  iterator end() const { return iterator(nullptr, this); }

  void clear();

  std::pair<iterator, bool> insertToTree(const key_type &key,
                                         const value_type &value,
                                         bool multi = false);

  std::pair<iterator, bool> insertToTree(std::pair<int, int> &value,
                                         bool multi = false);

  std::pair<iterator, bool> insertToTree(const value_type &value,
                                         bool multi = false);

  std::pair<iterator, bool> insertOrAssign(const key_type &key,
                                           const value_type &value);

  void erase(iterator pos);
  void merge(BinaryTree &other, bool multi = false);

  iterator find(const Key &key) const noexcept;
  bool contains(const Key &key) const noexcept;
  size_type count(const Key &key) const noexcept;

  std::pair<iterator, iterator> equal_range(const Key &key) const;
  iterator lower_bound(const Key &key) const;
  iterator upper_bound(const Key &key) const;

 private:
  void swap(BinaryTree &other);
  void clearTree(Node *root, BinaryTree &tree);
  void mergeTree(Node *node, BinaryTree *other, BinaryTree *tmp, bool multi);
  Node *copyTree(const Node *root);
  Node *getMinNode() const;
  Node *getMaxNode(Node *node) const;
  Node *findNode(const Key &key) const noexcept;
  Node *getNextNode(Node *node) const;
  Node *getPrevNode(Node *node) const;
  void setChildToParent(Node *child, Node *parent, bool isLeftChild);
  void setRoot(Node *node);
  void swapColor(Node *node);
  bool isLeftChild(Node *node);
  bool isRightChild(Node *node);
  bool isRed(Node *node) { return (node && node->getColor() == 'r'); }
  bool isBlack(Node *node) { return (!node || node->getColor() == 'b'); }
  bool isRoot(Node *node) { return (node == root_); }
  bool noParent(Node *node) { return (node && node->getParent() == nullptr); }
  void rotateLeft(Node *node);
  void rotateRight(Node *node);
  void insertBalancing(Node *node);
  void eraseBalancing(Node *node);
  Node *balancingLeftChild(Node *node);
  Node *balancingRightChild(Node *node);

  Node *root_ = nullptr;
  size_t nodeCount_ = 0;
  size_t size_max_ = std::numeric_limits<size_t>::max() / 2 / sizeof(Node);
};  // class MySet<Key>::BinaryTree

template <class Key, class T>
BinaryTree<Key, T> &BinaryTree<Key, T>::operator=(
    const BinaryTree<Key, T> &other) {
  BinaryTree tmp(other);
  swap(tmp);
  return *this;
}

template <class Key, class T>
BinaryTree<Key, T> &BinaryTree<Key, T>::operator=(
    BinaryTree<Key, T> &&other) noexcept {
  BinaryTree tmp(other);
  swap(tmp);
  return *this;
}

template <class Key, class T>
void BinaryTree<Key, T>::clear() {
  clearTree(root_, *this);
  root_ = nullptr;
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertToTree(const key_type &key, const value_type &value,
                                 bool multi) {
  if (contains(key) && !multi)
    return std::pair<iterator, bool>(find(key), false);

  Node *current = root_;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    current =
        (key < current->getKey()) ? current->getLeft() : current->getRight();
  }

  current = new Node(key, value);
  setChildToParent(current, parent, parent && key < parent->getKey());
  ++nodeCount_;

  if (isRed(parent)) insertBalancing(current);

  return std::pair<iterator, bool>(iterator(current, this), true);
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertToTree(std::pair<int, int> &value, bool multi) {
  return insertToTree(value.first, value.second, multi);
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertToTree(const T &value, bool multi) {
  return insertToTree(value, value, multi);
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertOrAssign(const key_type &key,
                                   const value_type &value) {
  if (!contains(key)) return insertToTree(key, value);
  findNode(key)->setValue(value);
  return std::pair<iterator, bool>(find(key), false);
}

template <class Key, class T>
void BinaryTree<Key, T>::insertBalancing(Node *node) {
  if (!node) return;
  if (node->getParent() && isBlack(node->getParent())) return;

  if (noParent(node)) {
    setRoot(node);

  } else if (isRed(node->getUncle())) {
    node->getParent()->setColor('b');
    node->getUncle()->setColor('b');
    node->grandpa()->setColor('r');
    insertBalancing(node->grandpa());

  } else if (isRightChild(node) && isLeftChild(node->getParent())) {
    rotateLeft(node->getParent());
    node = node->getLeft();

  } else if (isLeftChild(node) && isRightChild(node->getParent())) {
    rotateRight(node->getParent());
    node = node->getRight();
  }

  if (isRed(node->getParent())) {
    node->getParent()->setColor('b');
    node->grandpa()->setColor('r');

    if (isLeftChild(node) && isLeftChild(node->getParent())) {
      rotateRight(node->grandpa());
    } else {
      rotateLeft(node->grandpa());
    }
  }
}

template <class Key, class T>
void BinaryTree<Key, T>::erase(iterator pos) {
  if (pos == iterator(nullptr, this)) return;

  Node *node = findNode(pos->first);

  if (!node->getLeft() || !node->getRight()) {
    Node *child = node->getLeft() ? node->getLeft() : node->getRight();
    if (!child && isBlack(node)) eraseBalancing(node);
    setChildToParent(child, node->getParent(), isLeftChild(node));
    if (child && isBlack(node)) eraseBalancing(child);
  } else {
    Node *maxInLeft = getMaxNode(node->getLeft());
    node->setKey(maxInLeft->getKey());
    node->setValue(maxInLeft->getValue());
    if (!maxInLeft->getLeft() && isBlack(maxInLeft)) eraseBalancing(maxInLeft);
    setChildToParent(maxInLeft->getLeft(), maxInLeft->getParent(),
                     isLeftChild(maxInLeft));

    if (maxInLeft->getLeft() && isBlack(maxInLeft))
      eraseBalancing(maxInLeft->getLeft());
    node = maxInLeft;
  }

  delete node;
  node = nullptr;
  --nodeCount_;
}

template <class Key, class T>
void BinaryTree<Key, T>::eraseBalancing(Node *node) {
  if (!node || !(node->getBrother())) return;

  while (node != root_ && isBlack(node) && node) {
    if (isLeftChild(node)) {
      node = balancingLeftChild(node);
    } else {
      node = balancingRightChild(node);
    }
  }
  node->setColor('b');
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::balancingLeftChild(
    Node *node) {
  Node *brother = node->getBrother();
  if (isRed(brother)) {
    brother->setColor('b');
    (node->getParent())->setColor('r');
    rotateLeft(node->getParent());
    brother = (node->getParent())->getRight();
  }

  if (isBlack(brother->getLeft()) && isBlack(brother->getRight())) {
    brother->setColor('r');
    node = node->getParent();
  } else {
    if (isBlack(brother->getRight())) {
      if (brother->getLeft()) (brother->getLeft())->setColor('b');
      brother->setColor('r');
      rotateRight(brother);
      brother = (node->getParent())->getRight();
    }
    brother->setColor((node->getParent())->getColor());
    (node->getParent())->setColor('b');
    (brother->getRight())->setColor('b');
    rotateLeft(node->getParent());
    node = root_;
  }
  return node;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::balancingRightChild(
    Node *node) {
  Node *brother = node->getBrother();
  if (isRed(brother)) {
    brother->setColor('b');
    (node->getParent())->setColor('r');
    rotateRight(node->getParent());
    brother = (node->getParent())->getLeft();
  }
  if (isBlack(brother->getLeft()) && isBlack(brother->getRight())) {
    brother->setColor('r');
    node = node->getParent();
  } else {
    if (isBlack(brother->getLeft())) {
      if (brother->getRight()) (brother->getRight())->setColor('b');
      brother->setColor('r');
      rotateLeft(brother);
      brother = (node->getParent())->getLeft();
    }
    brother->setColor((node->getParent())->getColor());
    (node->getParent())->setColor('b');
    if (brother->getLeft()) (brother->getLeft())->setColor('b');
    rotateRight(node->getParent());
    node = root_;
  }
  return node;
}

template <class Key, class T>
void BinaryTree<Key, T>::swap(BinaryTree &other) {
  std::swap(root_, other.root_);
  std::swap(nodeCount_, other.nodeCount_);
}

template <class Key, class T>
void BinaryTree<Key, T>::merge(BinaryTree &other, bool multi) {
  BinaryTree<Key, T> tmp;
  mergeTree(other.root_, &other, &tmp, multi);
  if (multi) {
    clearTree(other.root_, other);
    other.root_ = nullptr;
  } else {
    other.swap(tmp);
    clearTree(tmp.root_, tmp);
    tmp.root_ = nullptr;
  }
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::find(
    const Key &key) const noexcept {
  return iterator(findNode(key), this);
}

template <class Key, class T>
bool BinaryTree<Key, T>::contains(const Key &key) const noexcept {
  return (findNode(key) != nullptr);
}

template <class Key, class T>
size_t BinaryTree<Key, T>::count(const Key &key) const noexcept {
  size_type count = 0;
  iterator it = find(key);
  for (; it != iterator(nullptr, this) && *it == key; ++it) {
    ++count;
  }
  return count;
}

template <class Key, class T>
std::pair<typename BinaryTree<Key, T>::iterator,
          typename BinaryTree<Key, T>::iterator>
BinaryTree<Key, T>::equal_range(const Key &key) const {
  iterator itBegin = find(key);
  iterator itEnd = itBegin;

  for (; itEnd != iterator(nullptr, this) && *itEnd == key; ++itEnd) {
  }
  return std::pair<iterator, iterator>(itBegin, itEnd);
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::lower_bound(
    const Key &key) const {
  iterator it = begin();
  for (; it != end() && *it < key; ++it) {
  }
  return it;
}

template <class Key, class T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::upper_bound(
    const Key &key) const {
  iterator it = begin();
  for (; it != end() && *it <= key; ++it) {
  }
  return it;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::getMinNode() const {
  if (!root_) return nullptr;

  Node *node = root_;
  while (node->getLeft()) {
    node = node->getLeft();
  }

  return node;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::getMaxNode(
    Node *node) const {
  if (!node) return nullptr;

  while (node->getRight()) {
    node = node->getRight();
  }

  return node;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::copyTree(
    const Node *root) {
  if (!root) return nullptr;

  Node *root_copy = new Node(root->getKey(), root->getValue());
  if (root_copy) {
    ++nodeCount_;
    root_copy->setColor(root->getColor());

    root_copy->setLeft(copyTree(root->getLeft()));
    if (root_copy->getLeft()) (root_copy->getLeft())->setParent(root_copy);

    root_copy->setRight(copyTree(root->getRight()));
    if (root_copy->getRight()) (root_copy->getRight())->setParent(root_copy);
  }

  return root_copy;
}

template <class Key, class T>
void BinaryTree<Key, T>::clearTree(Node *node, BinaryTree<Key, T> &tree) {
  if (!node) return;

  clearTree(node->getLeft(), tree);
  clearTree(node->getRight(), tree);

  delete node;
  --(tree.nodeCount_);
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::getNextNode(
    Node *node) const {
  if (!node) return getMaxNode(root_);

  Node *next = node;
  if (next->getRight()) {
    next = next->getRight();
    while (next->getLeft()) {
      next = next->getLeft();
    }
  } else {
    while (next->getParent() && next != (next->getParent())->getLeft()) {
      next = next->getParent();
    }
    next = next->getParent();
  }

  return (next != node) ? next : nullptr;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::getPrevNode(
    Node *node) const {
  if (!node) return getMaxNode(root_);

  Node *prev = node;
  if (prev->getLeft()) {
    prev = prev->getLeft();
    while (prev->getRight()) {
      prev = prev->getRight();
    }
  } else {
    while (prev->getParent() && prev != (prev->getParent())->getRight()) {
      prev = prev->getParent();
    }
    prev = prev->getParent();
  }

  return (prev != node) ? prev : nullptr;
}

template <class Key, class T>
void BinaryTree<Key, T>::mergeTree(Node *node, BinaryTree<Key, T> *other,
                                   BinaryTree<Key, T> *tmp, bool multi) {
  if (!node) return;

  mergeTree(node->getLeft(), other, tmp, multi);
  mergeTree(node->getRight(), other, tmp, multi);
  if (multi || !contains(node->getKey())) {
    insertToTree(node->getKey(), node->getValue(), multi);
  } else {
    tmp->insertToTree(node->getKey(), node->getValue(), multi);
  }
}

template <class Key, class T>
void BinaryTree<Key, T>::setChildToParent(Node *child, Node *parent,
                                          bool isLeftChild) {
  if (child) child->setParent(parent);
  if (parent) {
    if (isLeftChild) {
      parent->setLeft(child);
    } else {
      parent->setRight(child);
    }
  } else {
    setRoot(child);
  }
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::findNode(
    const Key &key) const noexcept {
  Node *current = root_;

  while (current && current->getKey() != key) {
    current =
        (key < current->getKey()) ? current->getLeft() : current->getRight();
  }

  return current;
}

template <class Key, class T>
bool BinaryTree<Key, T>::isLeftChild(Node *node) {
  return (node && node->getParent() && node == (node->getParent())->getLeft());
}

template <class Key, class T>
bool BinaryTree<Key, T>::isRightChild(Node *node) {
  return (node && node->getParent() && node == (node->getParent())->getRight());
}

template <class Key, class T>
void BinaryTree<Key, T>::setRoot(Node *node) {
  if (node) node->setColor('b');
  root_ = node;
}

template <class Key, class T>
void BinaryTree<Key, T>::swapColor(Node *node) {
  if (!node) return;

  if (isRed(node) || isRoot(node)) {
    node->setColor('b');
  } else {
    node->setColor('r');
  }
}

template <class Key, class T>
void BinaryTree<Key, T>::rotateLeft(Node *node) {
  if (!node) return;

  Node *pivot = node->getRight();
  setChildToParent(pivot, node->getParent(), isLeftChild(node));
  setChildToParent(pivot->getLeft(), node, false);
  setChildToParent(node, pivot, true);

  if (pivot && !pivot->getParent()) setRoot(pivot);
}

template <class Key, class T>
void BinaryTree<Key, T>::rotateRight(Node *node) {
  if (!node) return;

  Node *pivot = node->getLeft();
  setChildToParent(pivot, node->getParent(), isLeftChild(node));
  setChildToParent(pivot->getRight(), node, true);
  setChildToParent(node, pivot, false);

  if (pivot && !pivot->getParent()) setRoot(pivot);
}

template <class Key, class T>
class BinaryTree<Key, T>::Node {
 public:
  using key_type = Key;
  using value_type = T;

  Node() = delete;
  Node(key_type key) : Node(key, key) {}
  Node(key_type key, value_type value)
      : pair_(new std::pair<key_type, value_type>(key, value)) {}
  Node(const Node &other) : Node(other.key_, other.value_) {}
  Node(Node &&other) noexcept : Node(other.key_, other.value_) {}
  ~Node() { delete pair_; }

  Node &operator=(const Node &other);
  Node &operator=(Node &&other);

  Node *getLeft() const { return left_; }
  Node *getRight() const { return right_; }
  Node *getParent() const { return parent_; }
  key_type &getKey() const { return pair_->first; }
  value_type &getValue() const { return pair_->second; }
  char getColor() const { return color_; }
  std::pair<key_type, value_type> *getPair() const { return pair_; }
  Node *grandpa() { return (parent_) ? parent_->parent_ : nullptr; }
  Node *getUncle();
  Node *getBrother();

  void setLeft(Node *node) { left_ = node; }
  void setRight(Node *node) { right_ = node; }
  void setParent(Node *node) { parent_ = node; }
  void setKey(key_type key) { pair_->first = key; }
  void setValue(value_type value) { pair_->second = value; }
  void setColor(char color) { color_ = color; }

 private:
  Node *parent_ = nullptr;
  Node *left_ = nullptr;
  Node *right_ = nullptr;
  std::pair<key_type, value_type> *pair_ = nullptr;
  char color_ = 'r';
};  // class Node

template <class Key, class T>
typename BinaryTree<Key, T>::Node &BinaryTree<Key, T>::Node::operator=(
    const Node &other) {
  Node tmp(other);
  std::swap(pair_, tmp.pair_);
  return *this;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node &BinaryTree<Key, T>::Node::operator=(
    Node &&other) {
  std::swap(pair_, other.pair_);
  return *this;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::Node::getUncle() {
  if (!grandpa()) return nullptr;
  return (parent_ == grandpa()->left_) ? grandpa()->right_ : grandpa()->left_;
}

template <class Key, class T>
typename BinaryTree<Key, T>::Node *BinaryTree<Key, T>::Node::getBrother() {
  if (!parent_) return nullptr;
  return (parent_->left_ == this) ? parent_->right_ : parent_->left_;
}

template <class Key, class T>
class BinaryTree<Key, T>::TreeIterator
    : public BinaryTree<Key, T>::ConstTreeIterator {
 public:
  TreeIterator() : ConstTreeIterator() {}
  TreeIterator(Node *node, const BinaryTree<Key, T> *tree)
      : ConstTreeIterator(node, tree) {}
};  // class TreeIterator

template <class Key, class T>
class BinaryTree<Key, T>::ConstTreeIterator {
 public:
  ConstTreeIterator() = default;
  ConstTreeIterator(Node *node, const BinaryTree<Key, T> *tree)
      : node_(node), tree_(tree) {}

  T operator*();
  std::pair<key_type, value_type> *operator->();

  bool operator==(ConstTreeIterator it) { return (node_ == it.node_); }
  bool operator!=(ConstTreeIterator it) { return (node_ != it.node_); }

  ConstTreeIterator operator++();
  ConstTreeIterator operator--();

 private:
  Node *node_;
  std::pair<key_type, value_type> keyValue_;
  const BinaryTree<Key, T> *tree_;
};  // class ConstTreeIterator

template <class Key, class T>
T BinaryTree<Key, T>::ConstTreeIterator::operator*() {
  return (node_) ? node_->getValue()
                 : *(reinterpret_cast<const T *>(&(tree_->nodeCount_)));
}

template <class Key, class T>
std::pair<Key, T> *BinaryTree<Key, T>::ConstTreeIterator::operator->() {
  if (node_) return (node_->getPair());

  keyValue_.first = tree_->size();
  keyValue_.second = T();

  return &keyValue_;
}

template <class Key, class T>
typename BinaryTree<Key, T>::ConstTreeIterator
BinaryTree<Key, T>::ConstTreeIterator::operator++() {
  node_ = tree_->getNextNode(node_);
  return *this;
}

template <class Key, class T>
typename BinaryTree<Key, T>::ConstTreeIterator
BinaryTree<Key, T>::ConstTreeIterator::operator--() {
  node_ = tree_->getPrevNode(node_);
  return *this;
}

}  // namespace mycontainers

#endif  // __MY_CONTAINERS_MY_TREE_H__
