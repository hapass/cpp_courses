#include "sum_reverse_sort.h"
#include <algorithm>

using namespace std;

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    for (size_t i = 0; i < s.size() / 2; i++) {
        char temp = s[i];
        s[i] = s[s.size() - 1 - i];
        s[s.size() - 1 - i] = temp;
    }
    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}