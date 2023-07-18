namespace s21 {

/* ---------------- CONSTRUCTORS ------------------ */

template <typename T, size_t N>
Array<T, N>::Array() {}

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("too many initializers for Array");
  }
  std::copy(items.begin(), items.end(), begin());
  // fill 0, if items.size() > size()
  std::fill(begin() + items.size(), end(), 0);
}

template <typename T, size_t N>
Array<T, N>::Array(const Array &a) {
  std::copy(a.begin(), a.end(), begin());
}

template <typename T, size_t N>
Array<T, N>::Array(Array &&other) {
  std::move(other.begin(), other.end(), begin());
}

/* ------------------------ OPERATORS --------------------------- */

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(const Array &a) {
  if (this != &a) {
    std::copy(a.begin(), a.end(), begin());
  }

  return *this;
}

template <typename T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) {
  if (this != &a) {
    std::move(a.begin(), a.end(), begin());
  }

  return *this;
}

/* ------------------------- MODIFIRE ---------------------------- */

template <typename T, size_t N>
void Array<T, N>::swap(Array &other) {
  std::swap_ranges(other.begin(), other.end(), begin());
}

template <typename T, size_t N>
void Array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}

/* ---------------------------- ITERATORS ------------------------------ */

template <typename T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::begin() noexcept {
  return arr_;
}

template <typename T, size_t N>
constexpr typename Array<T, N>::const_iterator Array<T, N>::begin()
    const noexcept {
  return arr_;
}

template <typename T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::end() noexcept {
  return arr_ + size();
}

template <typename T, size_t N>
constexpr typename Array<T, N>::const_iterator Array<T, N>::end()
    const noexcept {
  return arr_ + size();
}

template <typename T, size_t N>
constexpr typename Array<T, N>::iterator Array<T, N>::data() noexcept {
  return arr_;
}

/* ---------------------------- ACCESS ------------------------------ */

template <typename T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::operator[](
    size_type pos) {
  return arr_[pos];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= size()) {
    throw std::out_of_range("Index out of range");
  }

  return arr_[pos];
}

template <typename T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::front() {
  return *begin();
}

template <typename T, size_t N>
constexpr typename Array<T, N>::reference Array<T, N>::back() {
  return *(end() - 1);
}

/* ---------------------------- CAPACITY ------------------------- */

template <typename T, size_t N>
constexpr bool Array<T, N>::empty() const noexcept {
  return size() == 0;
}

template <typename T, size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return N;
}

template <typename T, size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::max_size()
    const noexcept {
  return size();
}

};  // namespace s21
