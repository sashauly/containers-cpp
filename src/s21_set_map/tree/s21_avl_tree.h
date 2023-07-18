#ifndef CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_TREE_S21_AVL_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_TREE_S21_AVL_TREE_H_

#include <algorithm>
#include <initializer_list>
namespace s21 {

template <typename K, typename V>
struct Node {
  Node();
  Node(K o_value, int o_height);

  Node* next_node();
  Node* previous_node();

  K value;
  int height;
  Node *parent = nullptr, *left = nullptr, *right = nullptr;
};

template <typename K, typename V>
class AvlTree {
 public:
  class Iterator;
  class ConstIterator;

  using node_type = Node<K, V>;
  using reference = V&;
  using const_reference = const V&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  AvlTree() noexcept;
  explicit AvlTree(std::initializer_list<K> const& init);
  explicit AvlTree(const AvlTree& other);
  AvlTree(AvlTree&& other) noexcept;
  ~AvlTree();

  node_type* insert(const K& key);
  void merge(AvlTree& other);
  void erase(node_type*);
  node_type* find(const K& key);
  node_type* lower_bound(const K& key);
  void clear();

  bool empty() const;
  size_t get_size() const;
  size_t max_size() const;

  AvlTree& operator=(const AvlTree& other);
  AvlTree& operator=(AvlTree&& other);

  node_type* begin();
  node_type* end();

  class Iterator {
   public:
    Iterator();
    explicit Iterator(node_type* node);
    Iterator(const iterator& other);
    Iterator(iterator&& other);

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    iterator& operator=(const iterator& s);
    iterator& operator=(iterator&& s);
    bool operator!=(const iterator& it);
    bool operator==(const iterator& it);
    K& operator*();

   protected:
    node_type* iterator_node_;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator{} {};
    explicit ConstIterator(node_type* node) : Iterator{node} {};
    ConstIterator(const const_iterator& other) : Iterator{other} {};
    ConstIterator(const iterator& other) : Iterator{other} {};
    ConstIterator(const_iterator&& other) : Iterator{std::move(other)} {};
    const K& operator*();
  };

 private:
  size_t size_;
  node_type* head_;

  void delete_nodes(node_type* node);
  void swap_node(node_type* one, node_type* two);

  AvlTree& copy_tree(node_type* node, const node_type* other_node);
  AvlTree& swap_tree(AvlTree<K, V>&& other_tree);

  node_type* inner_insert(node_type* node, const K& key);

  void balance(node_type* node, int diff);
  int get_balance(const node_type* node) const;
  void balance_after_erase(node_type* node);

  int get_height(const node_type* node) const;
  void update_height(node_type* node);

  void left_rotate(node_type* node);
  void right_rotate(node_type* node);

  node_type* find_extremum(node_type* node, int balance);

  void create_end();
};
};  // namespace s21

#include "s21_avl_tree.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_SET_MAP_TREE_S21_AVL_TREE_H_