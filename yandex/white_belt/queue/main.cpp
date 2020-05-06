#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

int main() {
    int operationsCount = 0;
    cin >> operationsCount;

    //true -> worried, false -> quiet
    vector<bool> people;
    while (operationsCount > 0)
    {
        string operation;
        cin >> operation;

        if (operation == "WORRY") {
            int index = 0;
            cin >> index;

            assert(index >= 0 && index < people.size());
            people[index] = true;
        }
        else if (operation == "QUIET") {
            int index = 0;
            cin >> index;

            assert(index >= 0 && index < people.size());
            people[index] = false;
        }
        else if (operation == "COME") {
            int count = 0;
            cin >> count;
            people.resize(people.size() + count, false);
        }
        else if (operation == "WORRY_COUNT") {
            int count = 0;
            for (bool isWorried : people) {
                if (isWorried) {
                    count++;
                }
            }
            cout << count << endl;
        }

        operationsCount--;
    }

    return 0;
}