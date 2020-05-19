#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>

struct BusesForStopResponse {
    std::vector<std::string> buses;
};

struct StopsForBusResponse {
    std::vector<std::string> stops;
    std::map<std::string, std::vector<std::string>> interchanges;
};

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);