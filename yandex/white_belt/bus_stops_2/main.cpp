#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    map<vector<string>, int> routeToBusId;
    int busId = 0;
    while (commandsCount > 0)
    {
        int stopsCount = 0;
        cin >> stopsCount;

        vector<string> busStops(stopsCount);
        for (string& stop : busStops) {
            cin >> stop;
        }

        if (routeToBusId.count(busStops) == 0) {
            routeToBusId[busStops] = ++busId;
            cout << "New bus " << busId << endl;
        }
        else {
            cout << "Already exists for " << routeToBusId[busStops] << endl;
        }

        commandsCount--;
    }

    return 0;
}