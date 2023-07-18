namespace s21 {

/* -------- CONSTRUCTORS / DESTRUCTORS ---------- */

template <typename K, typename V>
AvlTree<K, V>::AvlTree() noexcept : size_{}, head_{} {};

template <typename K, typename V>
AvlTree<K, V>::AvlTree(std::initializer_list<K> const& init) : AvlTree() {
  for (auto i : init) insert(i);
};

template <typename K, typename V>
AvlTree<K, V>::AvlTree(const AvlTree<K, V>& other)
    : size_{other.size_}, head_{nullptr} {
  if (other.head_) {
    head_ = new Node<K, V>{other.head_->value, other.head_->height};
    create_end();
    copy_tree(head_, other.head_);
  }
};

template <typename K, typename V>
AvlTree<K, V>::AvlTree(AvlTree<K, V>&& other) noexcept
    : size_(other.size_), head_(other.head_) {
  other.head_ = nullptr;
  other.size_ = 0;
}

template <typename K, typename V>
AvlTree<K, V>::~AvlTree() {
  clear();
};

/* ------------------- OPERATORS --------------------- */

template <typename K, typename V>
AvlTree<K, V>& AvlTree<K, V>::operator=(const AvlTree<K, V>& other) {
  if (head_ == other.head_) return *this;
  clear();
  size_ = other.size_;
  if (other.size_)
    head_ = new Node<K, V>{other.head_->value, other.head_->height};
  return copy_tree(head_, other.head_);
};

template <typename K, typename V>
AvlTree<K, V>& AvlTree<K, V>::operator=(AvlTree<K, V>&& other) {
  return swap_tree(std::move(other));
};

/* ------------------- insert --------------------- */

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::inner_insert(Node<K, V>* node, const K& key) {
  Node<K, V>* tmp{};
  if (key > node->value && node->right) tmp = inner_insert(node->right, key);
  if (key < node->value && node->left) tmp = inner_insert(node->left, key);
  if (!node->right && key > node->value) {
    node->right = new Node<K, V>{key, 0};
    node->right->parent = node;
    tmp = node->right;
    ++size_;
  } else if (!node->left && key < node->value) {
    node->left = new Node<K, V>{key, 0};
    node->left->parent = node;
    tmp = node->left;
    ++size_;
  }
  update_height(node);
  balance(node, get_balance(node));
  return tmp;
}

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::insert(const K& key) {
  Node<K, V>* result{};
  if (!size_) {
    size_ = 1;
    head_ = new Node<K, V>{key, 0};
    result = head_;
    create_end();
  } else {
    result = inner_insert(head_, key);
  }
  return result;
}

template <typename K, typename V>
void AvlTree<K, V>::clear() {
  if (head_) {
    delete head_->parent;
    delete_nodes(head_);
    head_ = nullptr;
    size_ = 0;
  };
}

template <typename K, typename V>
void AvlTree<K, V>::delete_nodes(Node<K, V>* node) {
  if (node->left) delete_nodes(node->left);
  if (node->right) delete_nodes(node->right);
  delete node;
}

/* --------------- balance ------------------- */

template <typename K, typename V>
void AvlTree<K, V>::balance(Node<K, V>* node, int diff) {
  if (diff == 2) {
    if (get_balance(node->left) == -1) left_rotate(node->left);
    right_rotate(node);
  } else if (diff == -2) {
    if (get_balance(node->right) == 1) right_rotate(node->right);
    left_rotate(node);
  }
}

template <typename K, typename V>
void AvlTree<K, V>::right_rotate(Node<K, V>* node) {
  Node<K, V>* buffer = node->right;
  swap_node(node, node->left);
  node = node->parent;
  node->right = node->left;
  node->right->parent = node;
  node->left = node->left->left;
  if (node->left) node->left->parent = node;
  node->right->left = node->right->right;
  node->right->right = buffer;
  if (node->right->right) node->right->right->parent = node->right;
  update_height(node->right);
  update_height(node);
}

template <typename K, typename V>
void AvlTree<K, V>::left_rotate(Node<K, V>* node) {
  Node<K, V>* buffer = node->left;
  swap_node(node, node->right);
  node = node->parent;
  node->left = node->right;
  node->left->parent = node;
  node->right = node->right->right;
  if (node->right) node->right->parent = node;
  node->left->right = node->left->left;
  node->left->left = buffer;
  if (node->left->left) node->left->left->parent = node->left;
  update_height(node->left);
  update_height(node);
}

template <typename K, typename V>
void AvlTree<K, V>::update_height(Node<K, V>* node) {
  node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

template <typename K, typename V>
int AvlTree<K, V>::get_height(const Node<K, V>* node) const {
  return node ? node->height : -1;
}

template <typename K, typename V>
int AvlTree<K, V>::get_balance(const Node<K, V>* node) const {
  return get_height(node->left) - get_height(node->right);
}

/* ------------------- merge --------------------- */

template <typename K, typename V>
void AvlTree<K, V>::merge(AvlTree<K, V>& other) {
  Node<K, V>* inserted_node{};
  for (auto it = other.begin(); it != other.end();) {
    inserted_node = insert(it->value);
    if (inserted_node) {
      inserted_node = it;
      it = it->next_node();
      if (other.size_ == 1) it = nullptr;
      other.erase(inserted_node);
    } else {
      it = it->next_node();
    }
  };
}

/* ------------------ erase ---------------------- */

template <typename K, typename V>
void AvlTree<K, V>::erase(Node<K, V>* node) {
  Node<K, V>* tmp = node;
  if (!node->left && !node->right) {
    tmp = node->parent;
    if (tmp->left && node->value == tmp->left->value)
      tmp->left = nullptr;
    else if (tmp->right && node->value == tmp->right->value)
      tmp->right = nullptr;
    balance_after_erase(tmp);
    delete node;
    node = nullptr;
  } else if (!node->right) {
    swap_node(node, node->left);
    node = node->parent;
    node->height = 0;
    delete node->left;
    node->left = nullptr;
    if (head_->parent) balance_after_erase(node);
  } else if (!node->left) {
    swap_node(node, node->right);
    node = node->parent;
    node->height = 0;
    delete node->right;
    node->right = nullptr;
    if (head_->parent) balance_after_erase(node);
  } else {
    // tmp = find_extremum(tmp, get_balance(tmp));
    swap_node(node, find_extremum(tmp, get_balance(tmp)));
    erase(node);
  }
}

/* ---------------------- find ------------------------ */

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::find(const K& key) {
  Node<K, V>* tmp = head_;
  if (head_) {
    while (tmp) {
      if (key < tmp->value)
        tmp = tmp->left;
      else if (key > tmp->value)
        tmp = tmp->right;
      else
        break;
    }
    if (!tmp) tmp = head_->parent;
  }
  return tmp;
}

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::lower_bound(const K& key) {
  Node<K, V>* tmp = head_;
  Node<K, V>* res{};
  if (head_) {
    while (tmp) {
      if (key < tmp->value) {
        res = tmp;
        tmp = tmp->left;
      } else if (key > tmp->value) {
        tmp = tmp->right;
      } else {
        res = tmp;
        break;
      }
    }
  }
  return res;
};

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::find_extremum(Node<K, V>* node, int balance) {
  Node<K, V>* tmp{};
  if (balance < 0) {
    tmp = node->right;
    while (tmp->left) tmp = tmp->left;
  } else {
    tmp = node->left;
    while (tmp->right) tmp = tmp->right;
  }
  return tmp;
}

template <typename K, typename V>
void AvlTree<K, V>::balance_after_erase(Node<K, V>* node) {
  while (node->parent->parent != head_) {
    update_height(node);
    balance(node, get_balance(node));
    node = node->parent;
  }
  if (size_ == 1) {
    delete head_->parent;
    head_ = nullptr;
  }
  --size_;
}

/* -------------------- COPY AND SWAP ---------------------- */

template <typename K, typename V>
AvlTree<K, V>& AvlTree<K, V>::copy_tree(Node<K, V>* node,
                                        const Node<K, V>* other_node) {
  if (other_node) {
    if (other_node->left) {
      node->left =
          new Node<K, V>{other_node->left->value, other_node->left->height};
      node->left->parent = node;
      copy_tree(node->left, other_node->left);
    }
    if (other_node->right) {
      node->right =
          new Node<K, V>{other_node->right->value, other_node->right->height};
      node->right->parent = node;
      copy_tree(node->right, other_node->right);
    }
  }
  return *this;
}

template <typename K, typename V>
AvlTree<K, V>& AvlTree<K, V>::swap_tree(AvlTree<K, V>&& other_tree) {
  std::swap(head_, other_tree.head_);
  std::swap(size_, other_tree.size_);
  other_tree.clear();
  return *this;
}

template <typename K, typename V>
void AvlTree<K, V>::swap_node(Node<K, V>* one, Node<K, V>* two) {
  if (two->left) two->left->parent = one;
  if (two->right) two->right->parent = one;
  if (one->left == two || one->right == two) {
    if (one->left == two) {
      one->left = two->left;
      two->left = one;
      if (one->right) one->right->parent = two;
      std::swap(one->right, two->right);
    } else if (one->right == two) {
      one->right = two->right;
      two->right = one;
      if (one->left) one->left->parent = two;
      std::swap(one->left, two->left);
    }
    two->parent = one->parent;
    one->parent = two;
    if (one != head_) {
      if (two->parent->left == one)
        two->parent->left = two;
      else
        two->parent->right = two;
    }
  } else {
    if (two->parent->right == two)
      two->parent->right = one;
    else
      two->parent->left = one;
    if (one != head_) {
      if (one->parent->left == one)
        one->parent->left = two;
      else
        one->parent->right = two;
    }
    if (one->right) one->right->parent = two;
    if (one->left) one->left->parent = two;
    std::swap(one->right, two->right);
    std::swap(one->left, two->left);
    std::swap(one->parent, two->parent);
  }
  if (one == head_) {
    head_ = two;
    two->parent->parent = two;
  }
}

/* ---------------------- CAPACITY --------------------------- */

template <typename K, typename V>
bool AvlTree<K, V>::empty() const {
  return !head_;
};

template <typename K, typename V>
size_t AvlTree<K, V>::get_size() const {
  return size_;
};

template <typename K, typename V>
size_t AvlTree<K, V>::max_size() const {
  return (std::numeric_limits<size_t>::max() / 2) / sizeof(V) / 10;
};

/* -------------------- begin AND end ------------------------- */

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::begin() {
  Node<K, V>* tmp = head_;
  if (head_) {
    while (tmp->left) {
      tmp = tmp->left;
    }
  }
  return tmp;
};

template <typename K, typename V>
Node<K, V>* AvlTree<K, V>::end() {
  return head_ ? head_->parent : nullptr;
};

template <typename K, typename V>
void AvlTree<K, V>::create_end() {
  Node<K, V>* tmp = new Node<K, V>{head_->value, -1};
  tmp->parent = head_;
  head_->parent = tmp;
}

/* ------------------------ NODE ------------------------------ */

template <typename K, typename V>
Node<K, V>::Node() : value{}, height{} {};

template <typename K, typename V>
Node<K, V>::Node(K o_value, int o_height) : value{o_value}, height{o_height} {};

template <typename K, typename V>
Node<K, V>* Node<K, V>::next_node() {
  Node<K, V>* node = this;
  if (node->right) {
    node = node->right;
    while (node->left) node = node->left;
  } else {
    while (node->parent->parent != node && node->parent->value < node->value) {
      node = node->parent;
    }
    node = node->parent;
  }
  return node;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::previous_node() {
  Node<K, V>* node = this;
  if (node->parent->parent == node && node->height == -1) {
    node = node->parent;
    while (node->right) node = node->right;
  } else if (node->left) {
    node = node->left;
    while (node->right) node = node->right;
  } else {
    while (node->parent->value > node->value) {
      node = node->parent;
    }
    node = node->parent;
  }
  return node;
}

/* ---------------------------- ITERATOR ------------------------------ */

template <typename K, typename V>
AvlTree<K, V>::Iterator::Iterator() : iterator_node_{nullptr} {};

template <typename K, typename V>
AvlTree<K, V>::Iterator::Iterator(node_type* node) : iterator_node_{node} {};

template <typename K, typename V>
AvlTree<K, V>::Iterator::Iterator(const iterator& other)
    : iterator_node_{other.iterator_node_} {};

template <typename K, typename V>
AvlTree<K, V>::Iterator::Iterator(iterator&& other)
    : iterator_node_{other.iterator_node_} {
  other.iterator_node_ = nullptr;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator& AvlTree<K, V>::iterator::operator=(
    const iterator& it) {
  iterator_node_ = it.iterator_node_;
  return *this;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator& AvlTree<K, V>::iterator::operator=(
    iterator&& it) {
  iterator_node_ = it.iterator_node_;
  it.iterator_node_ = nullptr;
  return *this;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator AvlTree<K, V>::iterator::operator++(int) {
  iterator tmp = *this;
  operator++();
  return tmp;
};

template <typename K, typename V>
bool AvlTree<K, V>::iterator::operator!=(const iterator& it) {
  return iterator_node_ != it.iterator_node_;
};

template <typename K, typename V>
bool AvlTree<K, V>::iterator::operator==(const iterator& it) {
  return iterator_node_ == it.iterator_node_;
};

template <typename K, typename V>
K& AvlTree<K, V>::iterator::operator*() {
  if (iterator_node_) return iterator_node_->value;
  static K empty_value{};
  return empty_value;
};

template <typename K, typename V>
const K& AvlTree<K, V>::const_iterator::operator*() {
  if (const_iterator::iterator_node_)
    return const_iterator::iterator_node_->value;
  static K empty_value{};
  return empty_value;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator AvlTree<K, V>::iterator::operator--(int) {
  iterator tmp = *this;
  operator--();
  return tmp;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator& AvlTree<K, V>::iterator::operator++() {
  if (iterator_node_) iterator_node_ = iterator_node_->next_node();
  return *this;
};

template <typename K, typename V>
typename AvlTree<K, V>::iterator& AvlTree<K, V>::iterator::operator--() {
  if (iterator_node_) iterator_node_ = iterator_node_->previous_node();
  return *this;
};

};  // namespace s21