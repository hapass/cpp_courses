#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  ObjectPool() = default;

  T* Allocate() {
    T* object = nullptr;
    if (free_objects_.empty()) {
      object = new T;
    } else {
      object = free_objects_.front();
      free_objects_.pop();
    }
    allocated_objects_.insert(object);
    return object;
  }

  T* TryAllocate() {
    if (free_objects_.empty()) {
      return nullptr;
    }
    T* object = free_objects_.front();
    free_objects_.pop();
    allocated_objects_.insert(object);
    return object;
  }

  void Deallocate(T* object) {
    if (allocated_objects_.count(object) == 0) throw invalid_argument("no such object was allocated");
    allocated_objects_.erase(object);
    free_objects_.push(object);
  }

  ~ObjectPool() {
    while(!free_objects_.empty()) {
      delete free_objects_.front();
      free_objects_.pop();
    }

    for (T* object : allocated_objects_) {
      delete object;
    }
  }

private:
  queue<T*> free_objects_;
  set<T*> allocated_objects_;
};

void TestFreeObjectsAreStoredInQueue() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestFreeObjectsAreStoredInQueue);
  return 0;
}
