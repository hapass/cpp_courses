#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string code;
    cin >> code;
    if (code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) cin >> stop;
    } else if (code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    } else if (code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    } else if (code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

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

struct StopsForBusResponse {
    vector<string> stops;
    map<string, vector<string>> interchanges;
};

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

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus].clear();
        for (const string& stop : stops) {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        if (stops_to_buses.count(stop) != 0) {
            result.buses = stops_to_buses.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result;
        if (buses_to_stops.count(bus) != 0) {
            result.stops = buses_to_stops.at(bus);
            for (const string& stop : result.stops) {
                for (const string& other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        result.interchanges[stop].push_back(other_bus);
                    }
                }
            }
        }
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse result;
        result.buses_to_stops = buses_to_stops;
        return result;
    }
private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
