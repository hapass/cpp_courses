#include "query.h"

using namespace std;

istream& operator >> (istream& is, Query& q) {
    string code;
    is >> code;
    if (code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) is >> stop;
    } else if (code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}