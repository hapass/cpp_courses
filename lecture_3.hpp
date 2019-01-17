#pragma once

#include <iostream>

class Time {
    public: 
        Time(int hours, int minutes);
        Time(int minutes);
        Time();

        void print_time();
    private:
        int hours;
        int minutes;
};

void Time::print_time() {
    std::cout << hours << ":" << minutes << std::endl;
}

Time::Time(): Time(0, 0) {};
Time::Time(int minutes): Time(0, minutes) {}
Time::Time(int hours, int minutes): hours(hours), minutes(minutes) {}

void test_class() {
    Time().print_time();
}