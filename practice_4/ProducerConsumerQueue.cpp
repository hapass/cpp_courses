#include <vector>
#include "ProducerConsumerQueue.h"

template<class T>
ProducerConsumerQueue<T>::ProducerConsumerQueue(int size): size(size) {}

template<class T>
void ProducerConsumerQueue<T>::put(T element) {
    std::unique_lock<std::mutex> guard(sync);
    cv.wait(guard, [this](){ return queue.size() < size; });
    queue.push(element);
    guard.unlock();
    cv.notify_all();
}

template<class T>
T ProducerConsumerQueue<T>::get() {
    std::unique_lock<std::mutex> guard(sync);
    cv.wait(guard, [this](){ return queue.size() > 0; });
    auto value = queue.front();
    queue.pop();
    guard.unlock();
    cv.notify_all();
    return value;
}

template class ProducerConsumerQueue<int>;
template class ProducerConsumerQueue<std::vector<int>>;