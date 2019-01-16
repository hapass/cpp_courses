#include <iostream>
#include <string>
#include <stdio.h>

void sort(int* arr, int size, bool (*compare)(int, int)) {
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(compare(arr[j], arr[i])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void test_sort() {
    int arr[] { 4, 2, 3, 5, 6, 1 };
    int size = sizeof(arr)/sizeof(int);
    sort(arr, size, [](int a, int b) -> bool { return a > b; });

    for(int i = 0; i < size; i++) {
        printf("%d \n", arr[i]);
    }
}

void test_file() {
    auto pFile = fopen("data.txt", "r");

    if(pFile) {
        std::cout << "file opened" << std::endl;

        char str[1000];

        fgets(str, 1000, pFile);
        printf("%s\n", str);

        fclose(pFile);
    }
}

int main() {
    test_sort();
    test_file();
}