#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class ReversibleString {
public:
    ReversibleString() {}
    ReversibleString(string value): current_string(value) {}

    void Reverse() {
        for (int i = 0; i < current_string.size() / 2; i++) {
            char ch = current_string[current_string.size() - 1 - i];
            current_string[current_string.size() - 1 - i] = current_string[i];
            current_string[i] = ch;
        }
    }

    string ToString() const {
        return current_string;
    }
private:
    string current_string;
};

int main() {
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;
    
    s.Reverse();
    const ReversibleString& s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;
    
    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;
    
    return 0;
}