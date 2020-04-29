#pragma once

#include <queue>
#include <mutex>

template <class T>
class ProducerConsumerQueue {
    public:
        ProducerConsumerQueue(int size);
        void put(T element);
        T get();
    private:
        int size;
        std::mutex sync;
        std::condition_variable cv;
        std::queue<T> queue;
};