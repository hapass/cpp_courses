#include <iostream>
using namespace std;

int main() {
    double cost_no_discount = 0.0;
    double discount_threshold_one = 0.0;
    double discount_threshold_two = 0.0;
    double discount_one = 0.0;
    double discount_two = 0.0;

    cin >> cost_no_discount >> discount_threshold_one >> discount_threshold_two >> discount_one >> discount_two;

    double total_cost = cost_no_discount;

    if (cost_no_discount > discount_threshold_one)
    {
        total_cost = cost_no_discount * (1 - discount_one / 100);
    }

    if (cost_no_discount > discount_threshold_two)
    {
        total_cost = cost_no_discount * (1 - discount_two / 100);
    }

    cout << total_cost << endl;
    return 0;
}