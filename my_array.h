#ifndef MY_CONTAINERS_MY_ARRAY_H
#define MY_CONTAINERS_MY_ARRAY_H

namespace mycontainers {

template <class T, std::size_t N>
class array {
 public:
  class ArrayConstIterator;
  class ArrayIterator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();

  array &operator=(const array &a);
  array &operator=(array &&a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin() const;
  iterator end() const;

  bool empty() const noexcept;
  size_type size() noexcept;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type *data_ = nullptr;
  const size_type size_ = N;
};

template <class T, std::size_t N>
class array<T, N>::ArrayConstIterator {
 public:
  ArrayConstIterator(){};
  ArrayConstIterator(T *);

  T &operator*();
  typename array<T, N>::ArrayConstIterator operator++();
  typename array<T, N>::ArrayConstIterator operator--();
  bool operator==(const ArrayConstIterator it);
  bool operator!=(const ArrayConstIterator it);
  size_type operator-(const ArrayConstIterator it);

 private:
  const T *ptr_;
};

// class const_iterator foo begin

template <class T, std::size_t N>
array<T, N>::ArrayConstIterator::ArrayConstIterator(T *p) : ptr_(p) {}

template <class T, std::size_t N>
T &array<T, N>::ArrayConstIterator::operator*() {
  return *ptr_;
}

template <class T, std::size_t N>
typename array<T, N>::ArrayConstIterator
array<T, N>::ArrayConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <class T, std::size_t N>
typename array<T, N>::ArrayConstIterator
array<T, N>::ArrayConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <class T, std::size_t N>
bool array<T, N>::ArrayConstIterator::operator==(const ArrayConstIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T, std::size_t N>
bool array<T, N>::ArrayConstIterator::operator!=(const ArrayConstIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

// class const_iterator foo end

template <class T, std::size_t N>
class array<T, N>::ArrayIterator {
 public:
  ArrayIterator(){};
  ArrayIterator(T *);

  T &operator*();
  typename array<T, N>::ArrayIterator operator++();
  typename array<T, N>::ArrayIterator operator--();
  bool operator==(const ArrayIterator it);
  bool operator!=(const ArrayIterator it);

 private:
  T *ptr_;
};

// class iterator foo begin

template <class T, std::size_t N>
array<T, N>::ArrayIterator::ArrayIterator(T *p) : ptr_(p) {}

template <class T, std::size_t N>
T &array<T, N>::ArrayIterator::operator*() {
  return *ptr_;
}

template <class T, std::size_t N>
typename array<T, N>::ArrayIterator array<T, N>::ArrayIterator::operator++() {
  ++ptr_;
  return *this;
}

template <class T, std::size_t N>
typename array<T, N>::ArrayIterator array<T, N>::ArrayIterator::operator--() {
  --ptr_;
  return *this;
}

template <class T, std::size_t N>
bool array<T, N>::ArrayIterator::operator==(const ArrayIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T, std::size_t N>
bool array<T, N>::ArrayIterator::operator!=(const ArrayIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

// class iterator foo end

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

template <class T, std::size_t N>
void array<T, N>::swap(array &other) {
  if (size_ == other.size_) {
    array<T, N> tmp(*this);
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
      other.data_[i] = tmp.data_[i];
    }
  }
}

template <class T, std::size_t N>
size_t array<T, N>::max_size() const {
  return size_;
}

template <class T, std::size_t N>
size_t array<T, N>::size() noexcept {
  return size_;
}

template <class T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return size_ == 0 ? true : false;
}

template <class T, std::size_t N>
T *array<T, N>::begin() const {
  return data_;
}

template <class T, std::size_t N>
T *array<T, N>::end() const {
  return data_ + size_;
}

template <class T, std::size_t N>
T &array<T, N>::operator[](size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[pos];
}

template <class T, std::size_t N>
T &array<T, N>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[pos];
}

template <class T, std::size_t N>
T *array<T, N>::data() {
  return data_;
}

template <class T, std::size_t N>
const T &array<T, N>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[size_ - 1];
}

template <class T, std::size_t N>
const T &array<T, N>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("mycontainers::array::range_check");
  };
  return data_[0];
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) noexcept {
  if (this == &a) return *this;
  std::swap(data_, a.data_);
  return *this;
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  if (this == &a) return *this;
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
  return *this;
}

template <class T, std::size_t N>
array<T, N>::array() : size_(N) {
  data_ = new value_type[size_]();
}

template <class T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  data_ = new value_type[N]();
  auto iter = items.begin();
  for (size_type i = 0; i < items.size(); ++i) {
    data_[i] = *(iter + i);
  }
}

template <class T, std::size_t N>
array<T, N>::array(const array &a) : size_(a.size_) {
  data_ = new value_type[N]();
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, std::size_t N>
array<T, N>::array(array &&a) noexcept {
  std::swap(data_, a.data_);
}

template <class T, std::size_t N>
array<T, N>::~array() {
  if (data_) {
    delete[] data_;
  }
}

}  // namespace mycontainers

#endif  // MY_CONTAINERS_MY_ARRAY_H