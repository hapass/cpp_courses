#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> PalindromFilter(vector<string> words, int minLength) {
    vector<string> result;
    for (const string& word : words) {
        if (word.size() < minLength) {
            continue;
        }

        bool isPalindrome = true;
        for (int i = 0; i < word.size() / 2; i++) {
            if (word[i] != word[word.size() - 1 - i]) {
                isPalindrome = false;
                break;
            }
        }

        if (isPalindrome) {
            result.push_back(word);
        }
    }

    return result;
}

int main() {
    {
        int minLength = 5;
        vector<string> words = {"abacaba", "aba"};
        vector<string> output = PalindromFilter(words, minLength);
        for (const string& word : output)
        {
            cout << word << endl;
        }
    }
    cout << "_________" << endl;
    {
        int minLength = 2;
        vector<string> words = { "abacaba", "aba" };
        vector<string> output = PalindromFilter(words, minLength);
        for (const string& word : output)
        {
            cout << word << endl;
        }
    }
    cout << "_________" << endl;
    {
        int minLength = 4;
        vector<string> words = { "weew", "bro", "code" };
        vector<string> output = PalindromFilter(words, minLength);
        for (const string& word : output)
        {
            cout << word << endl;
        }
    }
    cout << "_________" << endl;
    {
        int minLength = 0;
        vector<string> words = { "madam", "gentleman", "x", "abba", "" };
        vector<string> output = PalindromFilter(words, minLength);
        for (const string& word : output)
        {
            cout << word << endl;
        }
    }
    cout << "_________" << endl;
    return 0;
}