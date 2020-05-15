#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint64_t block_count, block_density;
    cin >> block_count >> block_density;
    uint64_t sum = 0;
    while (block_count-- > 0) {
        uint64_t width, length, height;
        cin >> width >> length >> height;
        sum += block_density * width * length * height;
    }

    cout << sum << endl;
    return 0;
}