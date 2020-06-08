#include <vector>
#include <stdexcept>

template<typename T>
class Deque {
public:
  bool Empty() const {
    return size == 0;
  }

  void PushBack(const T& element) {
    back_data.push_back(element);
    size++;
  }

  void PushFront(const T& element) {
    front_data.push_back(element);
    size++;
  }

  size_t Size() const {
    return size;
  }

  T& operator[](size_t index) {
    size_t front_size = front_data.size();
    return index < front_size ? front_data.at(front_size - index - 1) : back_data.at(index - front_size);
  }

  const T& operator[](size_t index) const {
    size_t front_size = front_data.size();
    return index < front_size ? front_data.at(front_size - index - 1) : back_data.at(index - front_size);
  }

  T& At(size_t index) {
    size_t front_size = front_data.size();
    return index < front_size ? front_data.at(front_size - index - 1) : back_data.at(index - front_size);
  }

  const T& At(size_t index) const {
    size_t front_size = front_data.size();
    return index < front_size ? front_data.at(front_size - index - 1) : back_data.at(index - front_size);
  }

  T& Front() {
    return front_data.empty() ? back_data.front() : front_data.back();
  }

  const T& Front() const {
    return front_data.empty() ? back_data.front() : front_data.back();
  }

  T& Back() {
    return back_data.empty() ? front_data.front() : back_data.back();
  }

  const T& Back() const {
    return back_data.empty() ? front_data.front() : back_data.back();
  }

private:
  std::vector<T> front_data;
  std::vector<T> back_data;
  size_t size = 0;
};