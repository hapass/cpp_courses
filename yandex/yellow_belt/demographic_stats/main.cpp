#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    auto gb = partition(persons.begin(), persons.end(), [](const Person& p) {
        return p.gender == Gender::FEMALE;
    });

    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), gb) << endl;
    cout << "Median age for males = " << ComputeMedianAge(gb, persons.end()) << endl;

    auto feb = partition(persons.begin(), gb, [](const Person& p) {
        return p.is_employed;
    });

    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), feb) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(feb, gb) << endl;

    auto meb = partition(gb, persons.end(), [](const Person& p) {
        return p.is_employed;
    });

    cout << "Median age for employed males = " << ComputeMedianAge(gb, meb) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(meb, persons.end()) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}