#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

template<typename T> T Sqr(T x);
template<typename TValue> vector<TValue> Sqr(vector<TValue> x);
template<typename TKey, typename TValue> map<TKey, TValue> Sqr(map<TKey, TValue> x);
template<typename TFirst, typename TSecond> pair<TFirst, TSecond> Sqr(pair<TFirst, TSecond> x);

template<typename T> 
T Sqr(T x) {
    return x * x;
}

template<typename TValue> 
vector<TValue> Sqr(vector<TValue> x) {
    vector<TValue> result;
    for (const auto& v : x) {
        result.push_back(Sqr(v));
    }
    return result;
}

template<typename TKey, typename TValue> 
map<TKey, TValue> Sqr(map<TKey, TValue> x) {
    map<TKey, TValue> result;
    for (const auto& [key, value] : x) {
        result[key] = Sqr(value);
    }
    return result;
}

template<typename TFirst, typename TSecond> 
pair<TFirst, TSecond> Sqr(pair<TFirst, TSecond> x) {
    return pair<TFirst, TSecond>(Sqr(x.first), Sqr(x.second));
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
    cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}