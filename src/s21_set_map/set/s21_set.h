#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_SET_S21_SET_H_

#include "../tree/s21_avl_tree.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using node_type = Node<key_type, value_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AvlTree<key_type, value_type>::Iterator;
  using const_iterator = typename AvlTree<key_type, value_type>::ConstIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set(){};

  set &operator=(const set &s);
  set &operator=(set &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);

 private:
  AvlTree<key_type, value_type> tree_;
};
};  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_SET_S21_SET_H_
