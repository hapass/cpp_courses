#include "test_runner.h"
#include <string>
#include "my_deque.cpp"
using namespace std;

void TestEmpty() {
  {
    Deque<int> d;
    ASSERT(d.Empty());
  }

  {
    Deque<int> d;
    d.PushBack(1);
    ASSERT(!d.Empty());
  }

  {
    Deque<string> d;
    d.PushBack("str");
    ASSERT(!d.Empty());
  }

  {
    Deque<int> d;
    d.PushFront(2);
    ASSERT(!d.Empty());
  }
}

void TestSize()
{
  {
    Deque<int> d;
    d.PushBack(1);
    d.PushFront(2);
    ASSERT_EQUAL(d.Size(), 2);
  }

  {
    Deque<int> d;
    d.PushBack(1);
    ASSERT_EQUAL(d.Size(), 1);
  }

  {
    Deque<int> d;
    d.PushFront(1);
    ASSERT_EQUAL(d.Size(), 1);
  }
}

void TestGetElement() {
  {
    Deque<int> d;
    d.PushFront(2);
    d.PushFront(1);
    d.PushBack(3);
    d.PushBack(4);
    ASSERT_EQUAL(d[0], 1);
    ASSERT_EQUAL(d[1], 2);
    ASSERT_EQUAL(d.At(2), 3);
    ASSERT_EQUAL(d.At(3), 4);
  }

  {
    Deque<int> d;
    d.PushFront(2);
    d.PushFront(1);
    d.PushBack(3);
    d.PushBack(4);

    d[0] = 10;
    d.At(3) = 20;

    ASSERT_EQUAL(d[0], 10);
    ASSERT_EQUAL(d.At(3), 20);
  }

  {
    Deque<int> d;
    d.PushFront(2);
    d.PushFront(1);
    d.PushBack(3);
    d.PushBack(4);

    bool throws = false;
    try {
      d.At(4) = 1;
    } catch (out_of_range& e) {
      throws = true;
    }
    ASSERT(throws);
  }
}

void TestFrontAndBack() {
  Deque<int> d;
  d.PushFront(2);
  d.PushFront(1);
  d.PushBack(3);
  d.PushBack(4);

  d.Front() = 10;
  d.Back() = 20;

  ASSERT_EQUAL(d[0], 10);
  ASSERT_EQUAL(d[3], 20);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestSize);
  RUN_TEST(tr, TestGetElement);
  RUN_TEST(tr, TestFrontAndBack);
}
