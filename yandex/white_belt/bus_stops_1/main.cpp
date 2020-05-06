#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    map<string, vector<string>> stopToBuses;
    map<string, vector<string>> busToStops;
    while (commandsCount > 0)
    {
        string command;
        cin >> command;

        if (command == "NEW_BUS") {
            string bus;
            int stopCount = 0;
            cin >> bus >> stopCount;

            while (stopCount > 0) {
                string stop;
                cin >> stop;
                busToStops[bus].push_back(stop);
                stopToBuses[stop].push_back(bus);
                stopCount--;
            }
        } 
        else if (command == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;

            if (stopToBuses.count(stop) != 0) {
                stringstream ss;
                for (const auto& bus : stopToBuses.at(stop)) {
                    ss << bus << " ";
                }
                string buses = ss.str();
                cout << buses.substr(0, buses.size() - 1) << endl;
            }
            else {
                cout << "No stop" << endl;
            }
        }
        else if (command == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;

            if (busToStops.count(bus) != 0) {
                for (const auto& stop : busToStops.at(bus)) {
                    cout << "Stop "
                        << stop
                        << ": ";

                    stringstream ss;
                    for (const auto& currentBus : stopToBuses.at(stop)) {
                        if (bus != currentBus) {
                            ss << currentBus << " ";
                        }
                    }
                    string buses = ss.str();
                    cout << (buses == "" ? "no interchange" : buses.substr(0, buses.size() - 1)) << endl;
                }
            }
            else {
                cout << "No bus" << endl;
            }
        }
        else if (command == "ALL_BUSES") {
            if (busToStops.size() != 0) {
                for (const auto& [bus, stops] : busToStops) {
                    cout << "Bus "
                        << bus
                        << ": ";

                    stringstream ss;
                    for (const auto& stop : stops) {
                        ss << stop << " ";
                    }

                    string stopsString = ss.str();
                    cout << stopsString.substr(0, stopsString.size() - 1) << endl;
                }
            } else {
                cout << "No buses" << endl;
            }
        }
        commandsCount--;
    }

    return 0;
}