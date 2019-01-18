#include <thread>
#include "ProducerConsumerQueue.h"

void sort(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

static ProducerConsumerQueue<int> main_context(10);

int main() {
    static int arr[9] { 2, 4, 5, 6, 1, 4, 3, 0, 5 };

    std::thread p(sort, arr, 9);

    p.join();
}