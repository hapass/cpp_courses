#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>

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

void test_print_f() {
    int arr[] { 4, 2, 3, 5, 6, 1 };
    int size = sizeof(arr)/sizeof(int);
    sort(arr, size, [](int a, int b) -> bool { return a > b; });

    for(int i = 0; i < size; i++) {
        printf("%d \n", arr[i]);
    }
}

void test_fopen() {
    auto pFile = fopen("data.txt", "r");

    if(pFile) {
        std::cout << "file opened" << std::endl;

        char str[1000];

        fgets(str, 1000, pFile);
        printf("%s\n", str);

        fclose(pFile);
    }
}

void test_fstream() {
    std::ifstream myfile;
    myfile.open("data.txt");
    if(myfile.is_open()) {
        std::string line;
        std::getline(myfile, line);
        std::cout << line << std::endl;
    }
}

void test_cin() {
    int i;
    while(std::cin >> i) {
        if(i == 0) {
            break;
        }
        std::cout << "Input value: " << i << std::endl;
    }
}

void test_cout_manipulator() {
    bool isCool = true;
    float number = 2.345;
    std::cout << "Boolean: " << std::boolalpha << isCool << std::endl;
    std::cout << "Precision: " << std::setprecision(3) << number << std::endl;
}

int main() {
    // test_print_f();
    // test_fopen();
    // test_cin();
    // test_fstream();
    test_cout_manipulator();
}