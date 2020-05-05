#include <iostream>
#include <vector>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (const string& value : source) {
        destination.push_back(value);
    }

    source.clear();
}

int main() {
    vector<string> source = { "a", "b", "c" };
    vector<string> destination = { "z" };
    MoveStrings(source, destination);
    cout << "Source size: " << source.size() << endl;
    cout << "Destination: ";
    for (const string& value : destination) {
        cout << value << ' ';
    }
    cout << endl;
    return 0;
}