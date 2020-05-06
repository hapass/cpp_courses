#include <iostream>
#include <map>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    map<string, string> capitals;
    while (commandsCount > 0)
    {
        string command;
        cin >> command;

        if (command == "CHANGE_CAPITAL") {
            string country, capital;
            cin >> country >> capital;

            if (capitals.count(country) == 0)  {
                cout << "Introduce new country "
                    << country
                    << " with capital "
                    << capital
                    << endl;
                capitals[country] = capital;
            }
            else {
                if (capitals[country] != capital) {
                    cout << "Country " 
                        << country 
                        << " has changed its capital from "
                        << capitals[country]
                        << " to "
                        << capital
                        << endl;
                    capitals[country] = capital;
                }
                else {
                    cout << "Country " 
                        << country 
                        << " hasn't changed its capital" 
                        << endl;
                }
            }
        } 
        else if (command == "RENAME") {
            string oldCountryName, newCountryName;
            cin >> oldCountryName >> newCountryName;

            if (oldCountryName != newCountryName && 
                capitals.count(oldCountryName) != 0 && 
                capitals.count(newCountryName) == 0) {

                cout << "Country " 
                    << oldCountryName 
                    << " with capital "
                    << capitals[oldCountryName]
                    << " has been renamed to "
                    << newCountryName
                    << endl;
                
                string capital = capitals[oldCountryName];
                capitals.erase(oldCountryName);
                capitals[newCountryName] = capital;
            }
            else {
                cout << "Incorrect rename, skip" << endl;
            }
        }
        else if (command == "ABOUT") {
            string country;
            cin >> country;

            if (capitals.count(country) != 0) {
                cout << "Country "
                    << country
                    << " has capital "
                    << capitals[country]
                    << endl;
            }
            else {
                cout << "Country "
                    << country 
                    << " doesn't exist"
                    << endl;
            }
        }
        else if (command == "DUMP") {
            if (capitals.size() != 0) {
                string result;
                for (const auto& [country, capital] : capitals) {
                    result += country;
                    result += "/";
                    result += capital;
                    result += " ";
                }
                cout << result.substr(0, result.size() - 1) << endl;
            }
            else {
                cout << "There are no countries in the world" << endl;
            }
        }
        commandsCount--;
    }

    return 0;
}