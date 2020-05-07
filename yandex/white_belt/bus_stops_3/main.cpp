#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    int commandsCount = 0;
    cin >> commandsCount;

    map<set<string>, int> routeToBusId;
    int busId = 0;
    while (--commandsCount >= 0) {
        int stopsCount = 0;
        cin >> stopsCount;

        set<string> busStops;
        while (--stopsCount >= 0) {
            string stop;
            cin >> stop;
            busStops.insert(stop);
        }

        if (routeToBusId.count(busStops) == 0) {
            routeToBusId[busStops] = ++busId;
            cout << "New bus " << busId << endl;
        }
        else {
            cout << "Already exists for " << routeToBusId[busStops] << endl;
        }
    }

    return 0;
}