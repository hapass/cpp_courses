#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(string_view s) {
  vector<string_view> result;
  while (!s.empty()) {
    size_t pos = s.find(' ');
    if (pos != 0) result.push_back(s.substr(0, pos));
    s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
  }
  return result;
}

bool operator<(const SearchResult& lhs, const SearchResult& rhs) {
  if (lhs.hit_count == rhs.hit_count) return lhs.docid > rhs.docid;
  return lhs.hit_count < rhs.hit_count;
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

    map<size_t, size_t> docid_count;
    for (const auto& word : words) 
    for (const auto& [docid, hitcount] : index.Lookup(word)) 
      docid_count[docid] += hitcount;

    vector<SearchResult> search_results;
    search_results.reserve(docid_count.size());
    for (const auto& [docid, hitcount] : docid_count) {
      search_results.push_back({ hitcount, docid });
    }
    sort(rbegin(search_results), rend(search_results));

    search_results_output << current_query << ':';
    for (auto [hitcount, docid] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
}

void InvertedIndex::Add(string document) {
  docs.push_back(move(document));

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(docs.at(docid))) {
    index[word][docid]++;
  }
}

map<size_t, size_t> InvertedIndex::Lookup(string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
