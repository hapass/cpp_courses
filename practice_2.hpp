#pragma once

#include <vector>
#include <iostream>

void test_5(std::vector<int> vec) {
    int index = 1;
    while(index < vec.size() - 1) {
        int average = (vec[index - 1] + vec[index] + vec[index + 1]) / 3;
        if(vec[index] - average / 3 > average) {
            vec.erase(vec.begin() + index);
            index--;
        } else {
            index++;
        }
    }

    std::cout << "--------------------" << std::endl;
    std::for_each(vec.begin(), vec.end(), [](int& i) { std::cout << i << std::endl; });
    std::cout << "--------------------" << std::endl;
}

void test_6() {
    std::string str;
    std::cin >> str;
    std::reverse(str.begin(), str.end());
    std::cout << str << std::endl;
}