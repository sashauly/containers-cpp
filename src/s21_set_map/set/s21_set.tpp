namespace s21 {

/* ------------------ CONSTRUSCTORS / DESTRUCTOR ---------------- */

template <typename value_type>
set<value_type>::set() : tree_{} {};

template <typename value_type>
set<value_type>::set(std::initializer_list<value_type> const &items)
    : tree_{items} {};

template <typename value_type>
set<value_type>::set(const set &s) : tree_{s.tree_} {};

template <typename value_type>
set<value_type>::set(set &&s) : tree_{std::move(s.tree_)} {};

/* ------------------------ OPERATORS --------------------------- */

template <typename value_type>
set<value_type> &set<value_type>::operator=(const set<value_type> &s) {
  tree_ = s.tree_;
  return *this;
};

template <typename value_type>
set<value_type> &set<value_type>::operator=(set<value_type> &&s) {
  tree_ = std::move(s.tree_);
  return *this;
};

/* ------------------------ BEGIN / END -------------------------- */

template <typename value_type>
typename set<value_type>::iterator set<value_type>::begin() {
  return iterator(tree_.begin());
};

template <typename value_type>
typename set<value_type>::iterator set<value_type>::end() {
  return iterator(tree_.end());
};

/* ------------------------- CAPACITY ---------------------------- */

template <typename value_type>
bool set<value_type>::empty() {
  return tree_.empty();
};

template <typename value_type>
typename set<value_type>::size_type set<value_type>::size() {
  return tree_.get_size();
};

template <typename value_type>
typename set<value_type>::size_type set<value_type>::max_size() {
  return tree_.max_size();
};

/* ------------------------- MODIFIRE ---------------------------- */

template <typename value_type>
void set<value_type>::clear() {
  tree_.clear();
};

template <typename value_type>
std::pair<typename set<value_type>::iterator, bool> set<value_type>::insert(
    const value_type &value) {
  node_type *tmp = tree_.insert(value);
  iterator it{tmp};
  return std::pair(it, tmp);
};

template <typename value_type>
void set<value_type>::erase(iterator pos) {
  tree_.erase(tree_.find(*pos));
};

template <typename value_type>
void set<value_type>::swap(set<value_type> &other) {
  std::swap(tree_, other.tree_);
};

template <typename value_type>
void set<value_type>::merge(set<value_type> &other) {
  tree_.merge(other.tree_);
}

/* ----------------------------- LOOKUP ------------------------------- */

template <typename value_type>
typename set<value_type>::iterator set<value_type>::find(const key_type &key) {
  return iterator{tree_.find(key)};
};

template <typename value_type>
bool set<value_type>::contains(const key_type &key) {
  return tree_.find(key) != tree_.end();
};

}  // namespace s21