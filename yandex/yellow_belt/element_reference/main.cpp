#include <iostream>
#include <map>
#include <string>

using namespace std;

template<typename TKey, typename TValue>
TValue& GetRefStrict(map<TKey, TValue>& m, TKey v) {
    if (m.count(v) == 0) throw runtime_error("no such key");
    return m.at(v);
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}