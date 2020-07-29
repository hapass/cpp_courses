#include "stats.h"

#include <assert.h>
#include <iostream>

using namespace std;

HttpRequest ParseRequest(string_view line) {
  HttpRequest result;

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
  // not implemented
}

void Stats::AddUri(string_view uri) {
  // not implemented
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uri_stats;
}
