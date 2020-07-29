#include "stats.h"

#include <assert.h>
#include <iostream>

using namespace std;

HttpRequest ParseRequest(string_view line) {
  HttpRequest result;

  int prefix_space_count = 0;
  while (line[prefix_space_count] == ' ') prefix_space_count++;

  int suffix_space_count = 0;
  while (line[line.size() - 1 - suffix_space_count] == ' ') suffix_space_count++;

  line.remove_prefix(prefix_space_count);
  line.remove_suffix(suffix_space_count);

  size_t space_position = line.find(' ');
  if (space_position == string_view::npos) throw invalid_argument("no spaces in request header");

  result.method = line.substr(0, space_position);
  line.remove_prefix(space_position + 1);

  space_position = line.find(' ');
  if (space_position == string_view::npos) throw invalid_argument("only one space in request header");

  result.uri = line.substr(0, space_position);
  line.remove_prefix(space_position + 1);

  result.protocol = line;
  return result;
}

void Stats::AddMethod(string_view method) {
  if (method_stats.count(method) != 0) {
    method_stats.at(method)++;
  } else {
    method_stats.at("UNKNOWN")++;
  }
}

void Stats::AddUri(string_view uri) {
  if (uri_stats.count(uri) != 0) {
    uri_stats.at(uri)++;
  } else {
    uri_stats.at("unknown")++;
  }
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uri_stats;
}
