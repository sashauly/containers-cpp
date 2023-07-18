#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_VECTOR_S21_VECTOR_H_

#include <cmath>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class VectorIterator;

template <typename T>
class VectorConstIterator;

template <typename T>
class Vector {
 public:
  // Vector Member type
  using value_type = T;
  using reference_type = T&;
  using const_reference = const T&;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;

  //  Vector Member functions
  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v);
  ~Vector();

  Vector& operator=(const Vector& v);
  Vector& operator=(Vector&& v);

  // Vector Element access
  reference_type at(size_type pos);
  reference_type operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Vector Iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector& other);

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

  // Helpers
  void allocate(size_type new_cap);
  void bring_to_zero();
  void remove();
};

template <typename T>
class VectorIterator {
  friend class Vector<T>;
  friend class VectorConstIterator<T>;

 public:
  using value_type = T;
  using pointer_type = T*;
  using reference_type = T&;

  VectorIterator() : ptr_(){};
  VectorIterator(pointer_type ptr) : ptr_(ptr) {}

  VectorIterator& operator++() {
    ptr_++;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }
  VectorIterator& operator--() {
    ptr_--;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }
  VectorIterator operator+(const size_t value) {
    VectorIterator tmp(this->ptr_ + value);
    return tmp;
  }
  VectorIterator operator-(const size_t value) {
    VectorIterator tmp(this->ptr_ - value);
    return tmp;
  }
  bool operator==(const VectorIterator& other) const {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const VectorIterator& other) const {
    return ptr_ != other.ptr_;
  }
  reference_type operator*() const { return (*ptr_); }
  pointer_type operator->() { return ptr_; }

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  pointer_type ptr_;
};

template <typename T>
class VectorConstIterator {
  friend class Vector<T>;
  friend class VectorIterator<T>;

 public:
  using value_type = T;
  using pointer_type = T*;
  using reference_type = T&;

  VectorConstIterator() : ptr_(){};
  VectorConstIterator(pointer_type ptr) : ptr_(ptr) {}

  VectorConstIterator& operator++() {
    ptr_++;
    return *this;
  }
  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }
  VectorConstIterator& operator--() {
    ptr_--;
    return *this;
  }
  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --(*this);
    return tmp;
  }
  bool operator==(const VectorConstIterator& other) {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const VectorConstIterator& other) {
    return ptr_ != other.ptr_;
  }
  reference_type operator*() const { return (*ptr_); }
  pointer_type operator->() { return ptr_; }

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  pointer_type ptr_;
};
}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_VECTOR_S21_VECTOR_H_