#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    set<set<string>> synonyms;
    map<string, int> synonymCounts;
    while (--commandsCount >= 0)
    {
        string command;
        cin >> command;

        if (command == "ADD") {
            string firstWord, secondWord;
            cin >> firstWord >> secondWord;
            set<string> words = { firstWord, secondWord };
            if (synonyms.count(words) == 0) {
                synonyms.insert(words);
                synonymCounts[firstWord]++;
                synonymCounts[secondWord]++;
            }
            continue;
        }

        if (command == "COUNT") {
            string word;
            cin >> word;
            cout << synonymCounts[word] << endl;
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