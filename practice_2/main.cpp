#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

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

struct Phone {
    int code;
    int number;

    Phone(int code, int number) : code(code), number(number) {}
};

std::ostream& operator<< (std::ostream& out, const Phone& phone) {
    std::string number = std::to_string(phone.number);

    out 
        << '(' << std::setw(3) << std::setfill('0') << phone.code << ')'
        << ' ' << number.substr(0, 3) << '-' << number.substr(3, 2) << '-' << number.substr(5, 2);

    return out;
}

void test_2() {
    std::cout << Phone(29, 1234561) << std::endl;
}

template<class T>
void test_3(std::vector<T> list) {
    T sum = 0;
    for(auto i = list.begin(); i < list.end(); i++) {
        sum += *i;
    }
    std::cout << sum << "\n";
}

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

int main() {
    test_1();
    test_2();

    std::vector<int> integers { 1, 2, 3, 4, 5 };
    test_3(integers);

    std::vector<float> floats { 1.1, 2.2, 3.3, 4.4, 5.5 };
    test_3(floats);

    test_4();

    test_5({ 1, 1000, 1, 1 });
    test_5({ 1, 1000, 100, 2 });
    test_5({ 1, 1, 1, 1000 });
    test_5({ 1, 10, 100, 1000, 1 });

    test_6();
}