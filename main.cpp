#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <deque>

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
    float integer = 2;
    std::cout << "Boolean: " << std::boolalpha << isCool << "No: " << isCool << std::endl;
    std::cout << "Precision: " << std::setprecision(3) << number << std::endl;
    std::cout << "With point: " << std::showpoint << integer << std::endl;
    std::cout << std::setw(10) << std::setfill('_') << std::noshowpoint << integer << std::endl;
}

template<class T> void print(T* array, const int n) {
    for(int i = 0; i < n; i++) {
        std::cout << array[i] << std::endl;
    }
}

void test_print_array() {
    int integerArray[] { 1, 2, 3, 4, 5 };
    float floatArray[] { 1.1, 2.2, 3.3, 4.4, 5.5 };

    print(integerArray, sizeof(integerArray)/sizeof(int));
    print(floatArray, sizeof(floatArray)/sizeof(float));
}

void test_vector() {
    std::vector<int> vec { 4, 3, 1, 5, 8 };
    std::for_each(vec.begin(), vec.end(), [](int& i) { std::cout << i << std::endl; });
    std::sort(vec.begin(), vec.end());
    std::for_each(vec.begin(), vec.end(), [](int& i) { std::cout << i << std::endl; });
}

void test_deque() {
    std::deque<int> deq;
    deq.push_back(12);
    deq.push_back(15);

    int* p = &deq[0];
    p++;
    std::cout << "Dequeue: " << *p << std::endl;
}

void test_erase_5(std::vector<int> vec) {
    int offset = 1;
    while(true) {
        int current = vec[offset];

        if(offset >= vec.size() - 1) {
            break;
        }

        int previous = vec[offset - 1];
        int next = vec[offset + 1];
        int average = (previous + current + next) / 3;
        if(current - average / 3 > average) {
            vec.erase(vec.begin() + offset);
            offset = 1;
        } else {
            offset++;
        }
    }

    std::cout << "--------------------" << std::endl;
    std::for_each(vec.begin(), vec.end(), [](int& i) { std::cout << i << std::endl; });
    std::cout << "--------------------" << std::endl;
}

void test_revert_6() {
    std::string str;
    std::cin >> str;
    std::reverse(str.begin(), str.end());
    std::cout << str << std::endl;
}

int main() {
    //lection day 2
    //-------------
    // test_print_f();
    // test_fopen();
    // test_cin();
    // test_fstream();
    // test_cout_manipulator();
    // test_print_array();
    // test_vector();
    // test_deque();
    //-------------

    //practice day 2
    //-------------
    // test_erase_5({ 1, 1000, 1, 1 });
    // test_erase_5({ 1, 1000, 100, 2 });
    // test_erase_5({ 1, 1, 1, 1000 });
    // test_erase_5({ 1, 10, 100, 1000, 1 });
    // test_revert_6();
    //-------------
}