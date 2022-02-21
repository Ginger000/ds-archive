
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template<class T, class Compare>
size_t heap<T, Compare>::root() const {
  return 0;
}

template<class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const {
  return currentIdx * 2 + 1;
}

template<class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const {
  return currentIdx * 2 + 2;
}

template<class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const {
  return (currentIdx - 1) / 2;
}

template<class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const {
  return currentIdx * 2 + 1 < _elems.size();
}

template<class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const {
  size_t min = currentIdx;
  size_t l = leftChild(min), r = rightChild(min);
  if (l < _elems.size() && higherPriority(_elems[l], _elems[min]))
    min = l;
  if (r < _elems.size() && higherPriority(_elems[r], _elems[min]))
    min = r;
  return min;
}

template<class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx) {
  size_t smallest = maxPriorityChild(currentIdx);
  if (smallest != currentIdx) {
    std::swap(_elems[currentIdx], _elems[smallest]);
    heapifyDown(smallest);
  }
}

template<class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx) {
  if (currentIdx == root())
    return;
  size_t parentIdx = parent(currentIdx);
  if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
    std::swap(_elems[currentIdx], _elems[parentIdx]);
    heapifyUp(parentIdx);
  }
}

template<class T, class Compare>
heap<T, Compare>::heap() {
}

template<class T, class Compare>
heap<T, Compare>::heap(const std::vector<T> &elems) {
  _elems = elems;
  size_t i = (_elems.size() / 2) - 1;
  for (int j = i; j >= 0; j--)
    heapifyDown(j);
}

template<class T, class Compare>
T heap<T, Compare>::pop() {
  if (_elems.empty()) {
    throw 1;
  }
  if (_elems.size() == 1) {
    T out = _elems[root()];
    _elems.clear();
    return out;
  }

  T out = _elems[root()];
  _elems[root()] = _elems.back();
  _elems.pop_back();
  heapifyDown(root());
  return out;
}

template<class T, class Compare>
T heap<T, Compare>::peek() const {
  return _elems[root()];
}

template<class T, class Compare>
void heap<T, Compare>::push(const T &elem) {
  _elems.push_back(elem);
  heapifyUp(_elems.size() - 1);
}

template<class T, class Compare>
void heap<T, Compare>::updateElem(const size_t &idx, const T &elem) {
  size_t i = idx + root();
  _elems[i] = elem;
  heapifyDown(i);
  heapifyUp(i);
}

template<class T, class Compare>
bool heap<T, Compare>::empty() const {
  return _elems.empty();
}

template<class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> &heaped) const {
  for (size_t i = root(); i < _elems.size(); i++) {
    heaped.push_back(_elems[i]);
  }
}
