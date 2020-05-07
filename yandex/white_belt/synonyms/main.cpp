#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    set<set<string>> synonyms;
    while (--commandsCount >= 0)
    {
        string command;
        cin >> command;

        if (command == "ADD") {
            string firstWord, secondWord;
            cin >> firstWord >> secondWord;
            synonyms.insert({ firstWord, secondWord });
            continue;
        }

        if (command == "COUNT") {
            string word;
            cin >> word;
            int count = 0;
            for (const auto& pair : synonyms) {
                if (pair.count(word) == 1) {
                    count++;
                }
            }
            cout << count << endl;
            continue;
        }

        if (command == "CHECK") {
            string firstWord, secondWord;
            cin >> firstWord >> secondWord;
            cout << (synonyms.count({ firstWord, secondWord }) == 1 ? "YES" : "NO") << endl;
            continue;
        }
    }

    return 0;
}