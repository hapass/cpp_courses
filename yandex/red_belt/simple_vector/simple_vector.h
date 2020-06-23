#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector(): data_(nullptr), capacity_(0), size_(0) {}
  explicit SimpleVector(size_t size): data_(new T[size]), capacity_(size), size_(size) {}

  ~SimpleVector() {
    delete[] data_;
  }

  T& operator[](size_t index) {
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

  void PushBack(const T& value) {
    if (size_ == capacity_) {
      capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
      T* temp = new T[capacity_];
      for (int i = 0; i < size_; i++) {
        temp[i] = data_[i];
      }
      delete[] data_;
      data_ = temp;
    }
    data_[size_] = value;
    size_++;
  }

private:
  T* data_;
  size_t capacity_;
  size_t size_;
};
