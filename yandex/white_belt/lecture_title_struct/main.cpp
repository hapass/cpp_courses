#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Specialization {
    string value;
    explicit Specialization(const string& v): value(v) {}
};

struct Course {
    string value;
    explicit Course(const string& v): value(v) {}
};

struct Week {
    string value;
    explicit Week(const string& v): value(v) {}
};

struct LectureTitle {
  Specialization specialization;
  Course course;
  Week week;
  LectureTitle(Specialization s, Course c, Week w): specialization(s), course(c), week(w) {}
};

int main() {
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
    );
    return 0;
}