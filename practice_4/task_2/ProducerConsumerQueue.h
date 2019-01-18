#pragma once

#include <vector>
#include <mutex>

template <class T>
class ProducerConsumerQueue {
    public:
        ProducerConsumerQueue(int size);
    private:
        int size;
        std::mutex mut;
        std::vector<T> vec;
        void Put(T element);
        T Get();
};

template<class T>
ProducerConsumerQueue<T>::ProducerConsumerQueue(int size): size(size) {}

template<class T>
void Put(T element) {
    mut.lock();
    if(vec.size() < size)
        vec.push_back(element);
    }

}