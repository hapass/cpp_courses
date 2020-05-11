#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    double a, b, c;
    input >> a >> b >> c;
    cout << fixed << setprecision(3) << a << endl << b << endl << c << endl;
    return 0;
}