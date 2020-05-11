#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    cout << fixed << setprecision(3);
    double num;
    while(input >> num) 
        cout << num << endl;
    return 0;
}