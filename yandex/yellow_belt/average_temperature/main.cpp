#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    int64_t sum = 0;
    std::vector<int> temperatures(n);
    for (int& temperature : temperatures) {
        std::cin >> temperature;
        sum += temperature;
    }

    int64_t average = sum / static_cast<int64_t>(temperatures.size());
    std::vector<size_t> above_average_indices;
    for (size_t i = 0; i < temperatures.size(); i++) {
        if (temperatures[i] > average) {
            above_average_indices.push_back(i);
        }
    }

    std::cout << above_average_indices.size() << std::endl;
    for (size_t i = 0; i < above_average_indices.size(); i++) {
        std::cout << above_average_indices[i];
        if ((i + 1) != temperatures.size()) std::cout << ' ';
    }
    std::cout << std::endl;
    return 0;
}