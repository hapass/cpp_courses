#pragma once

#include <iostream>

namespace lecture_4 {
    void test_reinterpret() {
        int a = 0b1'00000000'00000000000000000000000;
        float b = *(float*)&a;
        std::cout << a << " is " << b << std::endl;
    }

    struct add_x {
        int x;
        add_x(int x) : x(x) {}

        int operator()(int y) const {
            return x + y;
        }
    };

    void test_functor() {
        add_x add_ten(10);
        std::cout << add_ten(1) << std::endl;
    }

    struct mul {
        void operator()(int x) const {
            std::cout << x * x << std::endl;
        }
    };

    void test_vector() {
        std::vector<int> vec { 1, 2, 3, 4, 5 };
        std::for_each(vec.begin(), vec.end(), mul());
    }
}