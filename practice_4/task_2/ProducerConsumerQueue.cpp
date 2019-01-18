#include <vector>
#include "ProducerConsumerQueue.h"

template<class T>
ProducerConsumerQueue<T>::ProducerConsumerQueue(int size): size(size) {}

template<class T>
void ProducerConsumerQueue<T>::Put(T element) {
    std::unique_lock<std::mutex> guard(sync);
    if(queue.size() < size) {
        queue.push(element);
    } else {
        get_event.wait(guard);
    }
    put_event.notify_all();
}

template<class T>
T ProducerConsumerQueue<T>::Get() {
    std::unique_lock<std::mutex> guard(sync);
    T value;
    if(queue.size() > 0) {
        value = queue.front();
        queue.pop();
    } else {
        put_event.wait(guard);
        value = queue.front();
        queue.pop();
    }

    get_event.notify_all();
    return value;
}

template class ProducerConsumerQueue<int>;
template class ProducerConsumerQueue<std::vector<int>>;