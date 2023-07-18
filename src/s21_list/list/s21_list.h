#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_LIST_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  struct Node;
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);
  list &operator=(const list &l);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void reverse();
  void unique();
  void sort();
  ListIterator insert(ListIterator pos, const_reference value);
  void erase(ListIterator pos);
  void splice(ListConstIterator pos, list &other);

  class ListIterator {
   public:
    ListIterator(){};
    ListIterator(Node *ptr) : ptr_(ptr){};

    reference operator*();

    ListIterator operator++(int);

    ListIterator operator--(int);

    ListIterator &operator++();

    ListIterator &operator--();

    bool operator==(ListIterator other);
    bool operator!=(ListIterator other);

   private:
    Node *ptr_ = nullptr;
    friend class list<T>;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other) : ListIterator(other) {}
    const_reference operator*() const;
  };

  struct Node {
    value_type value_;
    Node *prev_;
    Node *next_;

    Node(const value_type &value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  ListIterator begin();
  ListIterator end();
  ListConstIterator begin() const;
  ListConstIterator end() const;

 private:
  Node *head_;
  Node *tail_;
  Node *end_;
  size_type size_;

  void set_new_value_for_list(Node *active, Node *add);
  void installation_in_blank_list(Node *add);
  void installation_not_in_blank_list(Node *active, Node *add);
  void index_alignment();
};
}  // namespace s21
#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_LIST_S21_LIST_H_
