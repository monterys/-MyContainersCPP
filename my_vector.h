#ifndef MY_CONTAINERS_MY_VECTOR_H
#define MY_CONTAINERS_MY_VECTOR_H

namespace mycontainers {

template <class T>
class vector {
 public:
  class VectorConstIterator;
  class VectorIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = size_t;

  vector() noexcept;
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();

  vector &operator=(const vector &v);
  vector &operator=(vector &&v) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data() noexcept;

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  inline size_type size() const { return size_; }
  size_type max_size() const;
  void reserve(size_type size);
  inline size_type capacity() const { return capacity_; }
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *data_;
  size_type capacity_ = 0;
  size_type size_ = 0;
};

template <class T>
class vector<T>::VectorConstIterator {
 public:
  VectorConstIterator(){};
  VectorConstIterator(T *);

  T &operator*();
  typename vector<T>::VectorConstIterator operator++();
  typename vector<T>::VectorConstIterator operator--();
  bool operator==(const VectorConstIterator it);
  bool operator!=(const VectorConstIterator it);
  size_type operator-(const VectorConstIterator it);

 private:
  const T *ptr_;
};

template <class T>
class vector<T>::VectorIterator {
 public:
  VectorIterator(){};
  VectorIterator(T *);

  T &operator*();
  typename vector<T>::VectorIterator operator++();
  typename vector<T>::VectorIterator operator--();
  bool operator==(const VectorIterator it);
  bool operator!=(const VectorIterator it);
  size_type operator-(const VectorIterator it);

 private:
  T *ptr_;
};

// class const_iterator foo begin

template <class T>
vector<T>::VectorConstIterator::VectorConstIterator(T *p) : ptr_(p) {}

template <class T>
T &vector<T>::VectorConstIterator::operator*() {
  return *ptr_;
}

template <class T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <class T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <class T>
bool vector<T>::VectorConstIterator::operator==(const VectorConstIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T>
bool vector<T>::VectorConstIterator::operator!=(const VectorConstIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

template <class T>
size_t vector<T>::VectorConstIterator::operator-(const VectorConstIterator it) {
  return ptr_ - it.ptr_;
}

// class const_iterator foo end

// class iterator foo begin

template <class T>
vector<T>::VectorIterator::VectorIterator(T *p) : ptr_(p) {}

template <class T>
T &vector<T>::VectorIterator::operator*() {
  return *ptr_;
}

template <class T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <class T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <class T>
bool vector<T>::VectorIterator::operator==(const VectorIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

template <class T>
size_t vector<T>::VectorIterator::operator-(const VectorIterator it) {
  return ptr_ - it.ptr_;
  ;
}

// class iterator foo end

template <class T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <class T>
typename vector<T>::VectorIterator vector<T>::end() const {
  vector<T>::VectorIterator it(data_ + size_);
  return it;
}

template <class T>
typename vector<T>::VectorIterator vector<T>::begin() const {
  return iterator(data_);
}

template <class T>
typename vector<T>::VectorConstIterator vector<T>::cend() const {
  vector<T>::VectorConstIterator it(data_ + size_);
  return it;
}

template <class T>
typename vector<T>::VectorConstIterator vector<T>::cbegin() const {
  return const_iterator(data_);
}

template <class T>
void vector<T>::pop_back() {
  size_--;
}

template <class T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  data_[size_] = value;
  ++size_;
}

template <class T>
typename vector<T>::VectorIterator vector<T>::insert(iterator pos,
                                                     const_reference value) {
  size_type more = 1;
  if (size_ == capacity_) more += 1;
  size_type n = pos - begin();
  vector<value_type> tmp(capacity_ * more);
  size_type fl = 0;
  for (size_type i = 0; i < size_; ++i) {
    if (i == n) {
      tmp.data_[n] = value;
      ++i;
      ++size_;
      fl = 1;
    }
    tmp.data_[i] = data_[i - fl];
  }
  tmp.size_ = size_;
  *this = std::move(tmp);
  return data_ + n;
}

template <class T>
void vector<T>::erase(iterator pos) {
  size_type n = pos - begin();
  vector<value_type> tmp(size_);
  size_type fl = 0;
  for (size_type i = 0; i < size_; ++i) {
    if (i == n) {
      size_--;
      fl = 1;
    }
    tmp.data_[i] = data_[i + fl];
  }
  tmp.size_ = size_;
  *this = std::move(tmp);
}

template <class T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
size_t vector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <class T>
void vector<T>::shrink_to_fit() {
  vector<value_type> tmp(size_);
  for (size_type i = 0; i < size_; ++i) {
    tmp.data_[i] = data_[i];
  }
  *this = std::move(tmp);
}

template <class T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("vector::_M_range_check");
  }
  if (size > size_) {
    vector<value_type> tmp(size);
    for (size_type i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    tmp.size_ = size_;
    *this = std::move(tmp);
  }
}

template <class T>
T *vector<T>::data() noexcept {
  return data_;
}

template <class T>
const T &vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[size_ - 1];
}

template <class T>
const T &vector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[0];
}

template <class T>
T &vector<T>::operator[](size_type pos) const {
  return data_[pos];
}

template <class T>
T &vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("vector::_M_range_check");
  };
  return data_[pos];
}

template <class T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this == &v) return *this;
  std::swap(capacity_, v.capacity_);
  std::swap(size_, v.size_);
  std::swap(data_, v.data_);
  return *this;
}

template <class T>
vector<T> &vector<T>::operator=(const vector &v) {
  if (this == &v) return *this;
  capacity_ = v.capacity_;
  size_ = v.size_;
  data_ = new value_type[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
  return *this;
}

template <class T>
bool vector<T>::empty() const noexcept {
  return size_ == 0 ? true : false;
}

template <class T>
vector<T>::vector() noexcept : capacity_(0), size_(0) {}

template <class T>
vector<T>::vector(size_type n) : capacity_(n), size_(n) {
  data_ = new T[n]{};
}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : capacity_(items.size()), size_(items.size()) {
  data_ = new value_type[capacity_];
  auto iter = items.begin();
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = *(iter + i);
  }
}

template <class T>
vector<T>::vector(const vector &v) : capacity_(v.capacity_), size_(v.size_) {
  data_ = new value_type[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
}

template <class T>
vector<T>::vector(vector &&v) noexcept {
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
  std::swap(data_, v.data_);
}

template <class T>
vector<T>::~vector() {
  if (capacity_) {
    delete[] data_;
  }
}

template <class T>
template <typename... Args>
typename vector<T>::VectorIterator vector<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  if (!sizeof...(args)) return iterator(data_);
  vector<value_type> many{args...};
  size_type n = pos - cbegin();
  size_type new_size = size_ + many.size_;
  if (new_size > capacity_) reserve(new_size);
  vector<value_type> tmp(size_ - n);
  for (size_t i = 0; i < tmp.size_; ++i) {
    tmp.data_[i] = data_[i + n];
  }
  for (size_t i = 0; i < many.size_; ++i) {
    data_[i + n] = many.data_[i];
  }
  for (size_t i = 0; i < tmp.size_; ++i) {
    data_[i + n + many.size_] = tmp.data_[i];
  }
  size_ = new_size;
  return iterator(data_);
}

template <class T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  if (!sizeof...(args)) return;
  vector<value_type> many{args...};
  size_type new_size = size_ + many.size_;
  if (new_size > capacity_) reserve(new_size);
  for (size_t i = 0; i < many.size_; ++i) {
    data_[i + size_] = many.data_[i];
  }
  size_ = new_size;
}

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_VECTOR_H
