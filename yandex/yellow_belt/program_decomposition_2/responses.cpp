#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.size() == 0) {
        os << "No stop";
        return os;
    }
    bool is_first_bus = true;
    for (const string& bus : r.buses) {
        if (!is_first_bus) os << " ";
        is_first_bus = false;
        os << bus;
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.size() == 0) {
        os << "No bus";
    }
    bool is_first_stop = true;
    for (const string& stop : r.stops) {
        if (!is_first_stop) os << endl;
        is_first_stop = false;
        os << "Stop " << stop << ": ";
        if (r.interchanges.count(stop) == 0) {
            os << "no interchange";
        }
        else {
            bool is_first_interchange = true;
            for (const string& interchange : r.interchanges.at(stop)) {
                if (!is_first_interchange) os << " ";
                is_first_interchange = false;
                os << interchange;
            }
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool is_first_bus = true;
        for (const auto& bus_item : r.buses_to_stops) {
            if (!is_first_bus) os << endl;
            is_first_bus = false;

            os << "Bus " << bus_item.first << ": ";

            bool is_first_stop = true;
            for (const string& stop : bus_item.second) {
                if (!is_first_stop) os << " ";
                is_first_stop = false;
                os << stop;
            }
        }
    }
    return os;
}