#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Figure {
public:
    Figure(const string& name): name_(name) {}
    const string& Name() { return name_; };
    virtual const double Perimeter() = 0;
    virtual const double Area() = 0;
private:
    const string name_;
};

class Rect: public Figure {
public:
    Rect(int a, int b): Figure("RECT"), a_(a), b_(b) {}
    const double Perimeter() override {
        return 2 * (a_ + b_);
    }
    const double Area() override {
        return a_ * b_;
    }
private:
    int a_;
    int b_;
};

class Circle: public Figure {
public:
    Circle(int r): Figure("CIRCLE"), r_(r) {}
    const double Perimeter() override {
        return 2 * 3.14 * r_;
    }
    const double Area() override {
        return 3.14 * r_ * r_;
    }
private:
    int r_;
};

class Triangle: public Figure {
public:
    Triangle(int a, int b, int c): Figure("TRIANGLE"), a_(a), b_(b), c_(c) {}
    const double Perimeter() override {
        return a_ + b_ + c_;
    }
    const double Area() override {
        double s = (a_ + b_ + c_) / 2.0;
        return sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
private:
    int a_;
    int b_;
    int c_;
};

shared_ptr<Figure> CreateFigure(istream& stream) {
    string type;
    stream >> type;
    if (type == "RECT") {
        int a, b;
        stream >> a >> b;
        return make_shared<Rect>(a, b);
    } else if (type == "TRIANGLE") {
        int a, b, c;
        stream >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else {
        int r;
        stream >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}