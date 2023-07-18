#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_ARRAY_S21_ARRAY_H_
namespace s21 {
template <typename T, size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array() = default;

  Array<T, N> &operator=(const Array &a);
  Array<T, N> &operator=(Array &&a);

  constexpr reference at(size_type pos);
  constexpr reference operator[](size_type pos);
  constexpr reference front();
  constexpr reference back();
  constexpr iterator data() noexcept;
  constexpr iterator begin() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr iterator end() noexcept;
  constexpr const_iterator end() const noexcept;

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;
  void swap(Array &other);
  void fill(const_reference value);

 private:
  value_type arr_[N];
};
};  // namespace s21

#include "s21_array.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_ARRAY_S21_ARRAY_H_