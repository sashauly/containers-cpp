namespace s21 {
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : tree_{} {};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const &items) {
  for (auto it : items) {
    tree_.insert(it);
  }
};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map &m) : tree_{m.tree_} {};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map &&m) : tree_{std::move(m.tree_)} {};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type> &map<key_type, mapped_type>::operator=(
    const map &m) {
  tree_ = m.tree_;
  return *this;
};

template <typename key_type, typename mapped_type>
map<key_type, mapped_type> &map<key_type, mapped_type>::operator=(map &&m) {
  tree_ = std::move(m.tree_);
  return *this;
};

template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::at(const key_type &key) {
  node_type *tmp = tree_.lower_bound(value_type{key, mapped_type{}});
  if (!tmp || (tmp->value).first != key)
    throw std::out_of_range("Map dosen't contain this elem!");
  return tmp->value.second;
};

template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::operator[](const key_type &key) {
  node_type *tmp = tree_.lower_bound(value_type{key, mapped_type{}});
  if (!tmp || (tmp->value).first != key) {
    auto returned = tree_.insert(value_type{key, mapped_type{}});
    return returned->value.second;
  };
  return tmp->value.second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  return iterator{tree_.begin()};
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  return iterator{tree_.end()};
};

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() {
  return tree_.empty();
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() {
  return tree_.get_size();
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() {
  return tree_.max_size();
};

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  tree_.clear();
};

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type &value) {
  bool inserted{};
  node_type *tmp = tree_.lower_bound(value_type{value.first, mapped_type{}});
  if (!tmp || tmp->value.first != value.first) {
    inserted = true;
    tmp = tree_.insert(value);
  }
  iterator it{tmp};
  return std::pair<iterator, bool>{it, inserted};
};

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type &key,
                                   const mapped_type &obj) {
  bool inserted{};
  node_type *tmp = tree_.lower_bound(value_type{key, mapped_type{}});
  if (!tmp || tmp->value.first != key) {
    inserted = true;
    tmp = tree_.insert(value_type{key, obj});
  }
  iterator it{tmp};
  return std::pair<iterator, bool>{it, inserted};
};

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
  node_type *tmp = tree_.lower_bound(value_type{key, mapped_type{}});
  bool inserted{};
  if (tmp && (tmp->value).first == key) {
    tmp->value.second = obj;
  } else {
    tmp = tree_.insert(value_type{key, obj});
    inserted = true;
  }
  iterator it{tmp};
  return std::pair<iterator, bool>{it, inserted};
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  tree_.erase(tree_.lower_bound(*pos));
};

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map &other) {
  std::swap(tree_, other.tree_);
};

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map &other) {
  node_type *inserted_node{};
  for (auto it = other.begin(); it != other.end();) {
    inserted_node = tree_.lower_bound(value_type{(*it).first, mapped_type{}});
    if (!inserted_node || inserted_node->value.first != (*it).first) {
      insert(*it);
      inserted_node =
          other.tree_.lower_bound(value_type{(*it).first, mapped_type{}});
      ++it;
      if (other.size() == 1) it = iterator{nullptr};
      other.erase(iterator{inserted_node});
    } else {
      ++it;
    }
  }
};

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type &key) {
  auto res = tree_.lower_bound(value_type{key, mapped_type{}});
  return res && (res->value).first == key;
};

}  // namespace s21