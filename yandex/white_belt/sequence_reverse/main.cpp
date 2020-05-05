#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int>& v) {
    for (int i = 0; i < v.size() / 2; i++) {
        int temp = v[i];
        v[i] = v[v.size() - 1 - i];
        v[v.size() - 1 - i] = temp;
    }
}

int main() {
    vector<int> numbers = { 1, 5, 3, 4, 2 };
    Reverse(numbers);
    cout << "Numbers: ";
    for (int number : numbers) {
        cout << number << ' ';
    }
    cout << endl;
    return 0;
}