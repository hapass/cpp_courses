#pragma once

#include <cstdlib>
#include <utility>

template <typename T>
class SimpleVector {
public:
  SimpleVector(): data_(nullptr), capacity_(0), size_(0) {}
  explicit SimpleVector(size_t size): data_(new T[size]), capacity_(size), size_(size) {}

  ~SimpleVector() {
    delete[] data_;
  }

  SimpleVector<T>& operator=(const SimpleVector<T>& from) {
    delete[] data_;
    data_ = new T[from.Capacity()];
    size_ = from.Size();
    capacity_ = from.Capacity();
    for (size_t i = 0; i < from.Size(); i++) {
      data_[i] = from[i];
    }
    return *this;
  }

  T& operator[](size_t index) {
    return data_[index];
  }

  const T& operator[](size_t index) const {
    return data_[index];
  }

  T* begin() {
    return data_;
  }

  T* end() {
    return data_ + size_;
  }

  const T* begin() const {
    return data_;
  }

  const T* end() const {
    return data_ + size_;
  }

  size_t Size() const { return size_; }

  size_t Capacity() const {return capacity_; }

  void PushBack(T value) {
    if (size_ == capacity_) {
      capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
      T* temp = new T[capacity_];
      for (int i = 0; i < size_; i++) {
        temp[i] = std::move(data_[i]);
      }
      delete[] data_;
      data_ = temp;
    }
    data_[size_] = std::move(value);
    size_++;
  }

private:
  T* data_;
  size_t capacity_;
  size_t size_;
};
