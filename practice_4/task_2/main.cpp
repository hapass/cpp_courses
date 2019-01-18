#include <thread>
#include <iostream>
#include "ProducerConsumerQueue.h"

static ProducerConsumerQueue<std::vector<int>> main_context(10);

void sort(std::vector<int>& vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = i + 1; j < vec.size(); j++) {
            if(vec[j] < vec[i]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
            main_context.Put(vec);
        }
    }
}

int main() {
    std::vector<int> vec { 2, 4, 5, 6, 1, 4, 3, 0, 5 };

    std::thread p(sort, std::ref(vec));

    while(true) {
        std::vector<int> out = main_context.Get();
        std::for_each(out.begin(), out.end(), [](int& i){ std::cout << i; });
    }

    p.join();
}