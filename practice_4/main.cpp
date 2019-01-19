#include <thread>
#include <iostream>
#include "ProducerConsumerQueue.h"

static ProducerConsumerQueue<std::vector<int>> main_context(2);

void sort(std::vector<int> vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec.size() - i - 1; j++) {
            if(vec[j] > vec[j + 1]) {
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
                main_context.Put(vec);
            }
        }
    }
}

int main() {
    std::vector<int> vec { 2, 4, 5, 6, 1, 4, 3, 0, 5 };
    std::thread p(sort, vec);

    while(true) {
        std::vector<int> out = main_context.Get();
        std::for_each(out.begin(), out.end(), [](int& i){ std::cout << i << " "; });
        std::cout << std::endl;
    }
}