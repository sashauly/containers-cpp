#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_QUEUE_S21_QUEUE_H_

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& q);
  Queue(Queue&& q) noexcept;
  ~Queue();

  Queue<T>& operator=(const Queue& q);
  Queue<T>& operator=(Queue&& q) noexcept;

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(Queue& other);
  void clear();

  template <class... Args>
  void emplace_back(Args&&... args);

 private:
  struct Node {
    value_type value;
    Node* next;
  };

  Node* first_;
  Node* last_;
  size_type size_;
};
};  // namespace s21
#include "s21_queue.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_QUEUE_ARRAY_S21_QUEUE_S21_QUEUE_H_