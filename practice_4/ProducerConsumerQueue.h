#pragma once

#include <queue>
#include <mutex>

template <class T>
class ProducerConsumerQueue {
    public:
        ProducerConsumerQueue(int size);
        void Put(T element);
        T Get();
    private:
        int size;
        std::mutex sync;
        std::condition_variable cv;
        std::queue<T> queue;
};