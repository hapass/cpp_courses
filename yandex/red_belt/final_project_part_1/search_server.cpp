#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <array>
#include <sstream>
#include <iostream>

unordered_map<string_view, size_t> SplitIntoWords(string_view s) {
  unordered_map<string_view, size_t> result;
  while (!s.empty()) {
    size_t pos = s.find(' ');
    if (pos != 0) result[s.substr(0, pos)]++;
    s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
  }
  return result;
}

bool operator<(const SearchResult& lhs, const SearchResult& rhs) {
  if (lhs.hit_count == rhs.hit_count) return lhs.doc_id < rhs.doc_id;
  return lhs.hit_count > rhs.hit_count;
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

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
  unordered_map<size_t, size_t> doc_id_count;

  vector<SearchResult> search_results;
  search_results.reserve(6);

  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query);

    doc_id_count.clear();
    for (const auto [word, count] : words)
    for (const auto [doc_id, hitcount] : index.Lookup(word)) 
      doc_id_count[doc_id] += (hitcount * count);

    search_results.clear();
    for (const auto [doc_id, hitcount] : doc_id_count) {
      search_results.push_back({ hitcount, doc_id }); push_heap(search_results.begin(), search_results.end());
      if (search_results.size() == 6) {
        pop_heap(search_results.begin(), search_results.end()); search_results.pop_back();
      }
    }

    sort(search_results.begin(), search_results.end());

    search_results_output << current_query << ':';
    for (const auto& result : search_results) {
      search_results_output << " {docid: " << result.doc_id << ", hitcount: " << result.hit_count << '}';
    }
    search_results_output << '\n';
  }
}

void InvertedIndex::Add(string document) {
  docs.push_back(move(document));

  const size_t doc_id = docs.size() - 1;
  for (const auto& [word, hitcount] : SplitIntoWords(docs.at(doc_id))) {
    index[word][doc_id] = hitcount;
  }
}

const unordered_map<size_t, size_t>& InvertedIndex::Lookup(string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return empty;
  }
}
