namespace s21 {

/* ------------------ CONSTRUSCTORS / DESTRUCTOR ----------------- */

template <typename T>
Queue<T>::Queue() : first_(nullptr), last_(nullptr), size_(0) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items)
    : first_(nullptr), last_(nullptr), size_(0) {
  for (auto it = items.begin(); it < items.end(); it++) {
    push(*it);
  }
}

template <typename T>
Queue<T>::Queue(const Queue &q) : first_(nullptr), last_(nullptr), size_(0) {
  Node *tmp = q.first_;
  while (tmp) {
    push(tmp->value);
    tmp = tmp->next;
  }
}

template <typename T>
Queue<T>::Queue(Queue &&q) noexcept
    : first_(q.first_), last_(q.last_), size_(q.size_) {
  q.first_ = nullptr;
  q.last_ = nullptr;
  q.size_ = 0;
}

template <typename T>
Queue<T>::~Queue() {
  clear();
}

/* ------------------------ OPERATORS ---------------------------- */

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &q) {
  if (this == &q) return *this;

  clear();
  Node *tmp = q.first_;
  while (tmp) {
    push(tmp->value);
    tmp = tmp->next;
  }

  return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&q) noexcept {
  if (this == &q) return *this;

  clear();
  std::swap(first_, q.first_);
  std::swap(last_, q.last_);
  std::swap(size_, q.size_);

  return *this;
}

/* ------------------------ BEGIN / FRONT ------------------------ */

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  std::cout << "const_reference" << std::endl;
  return first_->value;
}

template <typename T>
typename Queue<T>::reference Queue<T>::front() {
  return first_->value;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  return last_->value;
}

template <typename T>
typename Queue<T>::reference Queue<T>::back() {
  return last_->value;
}

/* ------------------------- CAPACITY ---------------------------- */

template <typename T>
bool Queue<T>::empty() {
  return size() == 0;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() {
  return size_;
}

/* ------------------------- MODIFIRE ---------------------------- */

template <typename T>
void Queue<T>::push(const_reference value) {
  Node *tmp = new Node();
  tmp->value = value;
  tmp->next = nullptr;
  if (first_ == nullptr) {
    first_ = tmp;
    last_ = tmp;
  } else {
    last_->next = tmp;
    last_ = last_->next;
  }

  size_ += 1;
}

template <typename T>
void Queue<T>::pop() {
  if (first_) {
    Node *tmp = first_;
    first_ = first_->next;
    delete tmp;
    tmp = nullptr;
    size_ -= 1;
  }
}

template <typename T>
template <typename... Args>
void Queue<T>::emplace_back(Args &&...args) {
  value_type temp(std::forward<Args>(args)...);
  push(temp);
};

template <typename T>
void Queue<T>::swap(Queue &other) {
  std::swap(first_, other.first_);
  std::swap(last_, other.last_);
  std::swap(size_, other.size_);
}

template <typename T>
void Queue<T>::clear() {
  Node *tmp = nullptr;
  while (first_ != nullptr) {
    tmp = first_;
    first_ = first_->next;
    delete tmp;
    tmp = nullptr;
  }
  size_ = 0;
}

};  // namespace s21
