#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<int> table;
    int num;
    while(input >> num) {
        input.ignore(1);
        cout << num << endl;
        table.push_back(num);
    }

    for (int i = 0; i < table[0]; i++) {
        for (int j = 0; j < table[1]; j++) {
            cout << setw(10);
            cout << table[2 + i * table[1] + j];
            cout << ((j == (table[1] - 1)) ? ((i == (table[0] - 1)) ? "" : "\n") : " ");
        }
    }

    return 0;
}