namespace s21 {
//  Vector Member functions
template <typename value_type>
Vector<value_type>::Vector() : size_(0), capacity_(0), data_(nullptr) {}

template <typename value_type>
Vector<value_type>::Vector(size_type n) {
  if (n > max_size()) {
    throw std::length_error("Can't create s21::Vector larger than max_size()");
  }
  size_ = n;
  capacity_ = n;
  data_ = new value_type[capacity_];
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const& items)
    : size_(items.size()),
      capacity_(items.size()),
      data_(new value_type[capacity_]) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename value_type>
Vector<value_type>::Vector(const Vector& v)
    : size_(v.size_), capacity_(v.capacity_), data_(new value_type[capacity_]) {
  for (size_type i = 0; i < size_; i++) {
    data_[i] = v.data_[i];
  }
}

template <typename value_type>
Vector<value_type>::Vector(Vector&& v)
    : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
  v.bring_to_zero();
}

template <typename value_type>
Vector<value_type>::~Vector() {
  remove();
}

template <typename value_type>
typename s21::Vector<value_type>& Vector<value_type>::operator=(
    const Vector& v) {
  if (this != &v) {
    remove();
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; i++) {
      data_[i] = v.data_[i];
    }
  }
  return *this;
}

template <typename value_type>
typename s21::Vector<value_type>& Vector<value_type>::operator=(Vector&& v) {
  if (this != &v) {
    remove();
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = v.data_;
    v.bring_to_zero();
  }
  return *this;
}

// Vector Element access
template <typename value_type>
typename Vector<value_type>::reference_type Vector<value_type>::at(
    size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("Index is out of range");
  }
  return data_[pos];
}

template <typename value_type>
typename Vector<value_type>::reference_type Vector<value_type>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::front() {
  return *data_;
}

template <typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::back() {
  return *(data_ + size_ - 1);
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::data() {
  return data_;
}

// Vector Iterators
template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::begin() {
  return iterator(data_);
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::end() {
  return iterator(data_ + size_);
}

// Vector Capacity
template <typename value_type>
bool Vector<value_type>::empty() {
  return (size_ == 0);
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::size() {
  return size_;
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::max_size() {
  int bits = 63;
  if (sizeof(void*) == 4) {
    bits = 31;
  }
  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
}

template <typename value_type>
void Vector<value_type>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Size is too large");
  }
  if (size > size_) {
    allocate(size);
  }
}

template <typename value_type>
typename Vector<value_type>::size_type Vector<value_type>::capacity() {
  return capacity_;
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  if (size_ < capacity_) {
    allocate(size_);
  }
}

// Vector Modifiers
template <typename value_type>
void Vector<value_type>::clear() {
  size_ = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type position = &(*pos) - data_;
  size_type zero = 0;
  if (position < zero || position > size_) {
    throw std::out_of_range("Index is out ot range");
  }
  if (size_ + 1 >= capacity_) {
    allocate(size_ * 2);
  }
  value_type replace = data_[position];
  size_++;
  data_[position] = value;
  for (size_type i = position + 1; i < size_; ++i) {
    value_type next = data_[i];
    data_[i] = replace;
    replace = next;
  }
  return data_ + position;
}

template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  size_type position = &(*pos) - data_;
  size_type zero = 0;
  if (position < zero || position > size_) {
    throw std::out_of_range("Index is out ot range");
  }
  for (size_type i = position + 1; i < size_; i++) {
    data_[i - 1] = data_[i];
  }
  size_--;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    if (!size_) {
      allocate(1);
    } else {
      allocate(size_ * 2);
    }
  }
  data_[size_++] = value;
}

template <typename value_type>
void Vector<value_type>::pop_back() {
  if (size_ > 0) {
    size_--;
  }
}

template <typename value_type>
void Vector<value_type>::swap(Vector& other) {
  using std::swap;
  swap(size_, other.size_);
  swap(capacity_, other.capacity_);
  swap(data_, other.data_);
}

// Helpers

template <typename value_type>
void Vector<value_type>::allocate(size_type new_cap) {
  value_type* new_data = new value_type[new_cap];
  for (size_type i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_cap;
}

template <typename value_type>
void Vector<value_type>::bring_to_zero() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename value_type>
void Vector<value_type>::remove() {
  delete[] this->data_;
  bring_to_zero();
}

}  // namespace s21