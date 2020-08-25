#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct SearchResult {
  size_t hit_count;
  size_t docid;
};

class InvertedIndex {
public:
  InvertedIndex() { docs.reserve(50000); }

  void Add(string document);
  const map<size_t, size_t>& Lookup(string_view word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

private:
  map<string_view, map<size_t, size_t>> index;
  map<size_t, size_t> empty;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
