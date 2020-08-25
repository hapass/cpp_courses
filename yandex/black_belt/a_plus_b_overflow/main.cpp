#include <iostream>
#include <exception>
#include <numeric>

using namespace std;

int64_t sum(int64_t a, int64_t b) {
  if (a == 0) return b;
  else if (b == 0) return a;
  else if ((a < 0 && b > 0) || (a > 0 && b < 0)) return a + b;

  int n = 64;
  int carry = 0;
  int carry_to_sign = 0;
  while (n != 0) {
    int shift = 64 - n;
    int bit_a = (a >> shift) & 0x00'00'00'00'00'00'00'01;
    int bit_b = (b >> shift) & 0x00'00'00'00'00'00'00'01;
    if (bit_a + bit_b + carry > 1) carry = 1;
    else carry = 0;
    if (shift == 62) carry_to_sign = carry;
    n--;
  }

  if (carry_to_sign != carry) throw runtime_error("overflow");
  return a + b;
}

int main() {
  int64_t a, b;
  cin >> a >> b;

  try {
    cout << sum(a, b) << endl;
  } catch (const exception& e) {
    cout << "Overflow!" << endl;
  }

  return 0;
}