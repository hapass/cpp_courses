#pragma once

#include "http_request.h"
#include <string_view>
#include <map>

using namespace std;

class Stats {
public:
  Stats(): uri_stats({
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0},
  }), method_stats({
    {"GET", 0},
    {"PUT", 0},
    {"POST", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0},
  }) {}

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
  map<string_view, int> uri_stats;
  map<string_view, int> method_stats;
};

HttpRequest ParseRequest(string_view line);
