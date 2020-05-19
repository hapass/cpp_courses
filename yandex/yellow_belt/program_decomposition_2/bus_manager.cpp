#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus].clear();
    for (const string& stop : stops) {
        buses_to_stops[bus].push_back(stop);
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse result;
    if (stops_to_buses.count(stop) != 0) {
        result.buses = stops_to_buses.at(stop);
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse result;
    result.buses_to_stops = buses_to_stops;
    return result;
}