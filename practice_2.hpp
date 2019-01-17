#pragma once

#include <vector>
#include <iostream>
#include <fstream>

/*
    Read file with 3 words.
    Print first word aligned by left side.
    Print second word aligned by center.
    Print last word aligned by right side.
*/
int center(int width, std::string word) {
    return (width - word.length()) / 2;
}

int left(int width, std::string word) {
    return width - center(width, word) - word.length();
}

void test_1() {
    std::ifstream words;
    words.open("words.txt");

    if(words.is_open()) {
        std::string first_word;
        std::string second_word;
        std::string third_word;

        words >> first_word >> second_word >> third_word;
        
        int width = 40;
        char fill = '*';

        std::cout 
            << std::setw(width) << std::setfill(fill) << std::left << first_word << std::endl
            << std::string(center(width, second_word), fill) << second_word << std::string(left(width, second_word), fill) << std::endl
            << std::setw(width) << std::right << third_word << std::endl;
    }
}

/*
    Override << operator for structure containing mobile phone number.
*/
struct Phone {
    int code;
    int number;
};

std::ostream& operator<< (std::ostream& out, const Phone& phone) {
    std::string number = std::to_string(phone.number);

    out 
        << '(' << std::setw(3) << std::setfill('0') << phone.code << ')'
        << ' ' << number.substr(0, 3) << '-' << number.substr(3, 2) << '-' << number.substr(5, 2);

    return out;
}

void test_2() {
    Phone phone;
    phone.code = 29;
    phone.number = 1234561;

    std::cout << phone << std::endl;
}

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
    std::ifstream cities;
    cities.open("cities.txt");
    std::vector<std::pair<int, std::string>> list;
    if(cities.is_open()) {
        std::string name;
        int distance;
        while(cities >> name >> distance) {
            std::pair<int, std::string> pair(distance, name);
            list.push_back(pair);
        }
    }

    std::sort(list.begin(), list.end(), [](std::pair<int, std::string>& first, std::pair<int, std::string>& second){
        return first.first < second.first;
    });
    
    if(list.size() > 0) {
        std::cout << list[0].second << std::endl;
    } else {
        std::cout << "list is empty" << std::endl;
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