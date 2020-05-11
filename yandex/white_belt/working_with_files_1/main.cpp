#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream stream("input.txt");
    string temp;
    while (getline(stream, temp)) {
        cout << temp << endl;
    }
    return 0;
}