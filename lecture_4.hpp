#pragma once

#include <iostream>
#include <algorithm>

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

    struct square {
        void operator()(int x) const {
            std::cout << x * x << std::endl;
        }
    };

    void test_stl_functor() {
        std::vector<int> vec { 1, 2, 3, 4, 5 };
        std::for_each(vec.begin(), vec.end(), square());
    }

    template<class T>
    struct cube {
        void operator()(T& x) const {
            std::cout << x * x * x << std::endl;
        }
    };

    void test_template_functor() {
        std::vector<int> vec { 1, 2, 3, 4, 5 };
        std::for_each(vec.begin(), vec.end(), cube<int>());

        std::vector<float> vecf { 1.1, 2.2, 3.3, 4.5, 5.6 };
        std::for_each(vecf.begin(), vecf.end(), cube<float>());
    }

    void fill_vector(std::vector<int>& v) {
        static int n = 1;
        std::generate(v.begin(), v.end(), []{ return n++; });
    }

    void test_lambda() {
        std::vector<int> vec(20);
        fill_vector(vec);
        std::for_each(vec.begin(), vec.end(), [](int& i){ std::cout << i << std::endl; } );
    }
}