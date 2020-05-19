#include "sum_reverse_sort.h"

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
    int size = static_cast<int>(nums.size());
    for (int i = 1; i < size; i++) {
       for (int j = i; j >= 0; j--) {
           if (nums[j - 1] > nums[j]) {
               int temp = nums[j - 1];
               nums[j - 1] = nums[j];
               nums[j] = temp;
           }
       }
    }
}