#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <deque>

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
    std::ifstream myFile;
    myFile.open("data.txt");
    if(myFile.is_open()) {
        std::string line;
        std::getline(myFile, line);
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

void test_cout() {
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

void test_template() {
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