#pragma once

#include <vector>
#include <iostream>
#include <fstream>

/*
    Override << operator for structure containing mobile phone number.
*/


/*
    Find a sum of elements in a list.
    Method should be templated for use with float and int.
*/
template<class T>
void test_3(std::vector<T> list) {
    T sum = 0;
    for(auto i = list.begin(); i < list.end(); i++) {
        sum += *i;
    }
    std::cout << sum << "\n";
}

/*
    Read a list of pairs from file. Pairs containt city name and distance to the city from current location.
    Find city name by distance and display it.
    Use pair and vector.
*/
void test_4() {
    int targetDistance;
    std::cin >> targetDistance;

    std::ifstream cities;
    cities.open("data.txt");
    std::vector<std::pair<int, std::string>> list;
    if(cities.is_open()) {
        std::string name;
        int distance;
        while(cities >> name >> distance) {
            std::pair<int, std::string> pair(distance, name);
            list.push_back(pair);
        }
    }

    auto iterator = std::find_if(list.begin(), list.end(), [&](std::pair<int, std::string>& p){ return p.first == targetDistance; });
    
    if(iterator != list.end()) {
        std::cout << iterator->second << '\n';
    } else {
        std::cout << "nothing found" << '\n';
    }
}

/*
    Given a vector of numbers. Remove one by one numbers, that:
     * have left and right neighbours
     * and a magnitude of twice the average of the element itself and its neighbours.
    Use STL.
*/
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

/*
    Read a string from file and revert it.
    Use STL.
*/
void test_6() {
    std::string str;
    std::cin >> str;
    std::reverse(str.begin(), str.end());
    std::cout << str << std::endl;
}