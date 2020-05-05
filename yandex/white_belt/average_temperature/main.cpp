#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    int sum = 0;
    vector<int> temperatures(n);
    for (int& temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum / temperatures.size();

    vector<int> aboveAverageDays;
    for (int i = 0; i < temperatures.size(); i++) {
        if (temperatures[i] > average) {
            aboveAverageDays.push_back(i);
        }
    }

    cout << aboveAverageDays.size() << endl;
    for (int day : aboveAverageDays) {
        cout << day << ' ';
    }
    cout << endl;
    return 0;
}