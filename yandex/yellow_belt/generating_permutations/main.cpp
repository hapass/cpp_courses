#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> numbers;
    while (n-- > 0) numbers.push_back(n + 1);

    do
    {
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << endl;
    } while(prev_permutation(numbers.begin(), numbers.end()));

    return 0;
}
