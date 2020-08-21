#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <future>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator+=(const Stats& other) {
    for (const auto& [key, value] : other.word_frequences) word_frequences[key] += value;
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats result;
  size_t pos = 0;
  size_t previous_pos = 0;
  string_view line_view(line);
  while (true) {
    pos = line_view.find(' ', previous_pos);
    string word = string(line_view.substr(previous_pos, pos - previous_pos));
    if (key_words.find(word) != key_words.end()) result.word_frequences[word]++;
    if (pos == string_view::npos) break;
    previous_pos = pos + 1;
  }
  return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<string> all_lines;
  for (string line; getline(input, line); ) all_lines.push_back(line);
  size_t processors_count = 8;
  size_t parts = all_lines.size() < processors_count ? 1 : processors_count;
  size_t chunk_size = all_lines.size() / parts;

  vector<stringstream> chunks(parts);
  for (size_t i = 0; i < chunks.size(); i++) {
    size_t chunk_start = i * chunk_size;
    size_t chunk_end = i == (chunks.size() - 1) ? all_lines.size() : chunk_start + chunk_size;
    for (size_t j = chunk_start; j < chunk_end; j++) {
      chunks[i] << all_lines[j] << '\n';
    }
  }

  vector<future<Stats>> stats;
  for (auto& chunk : chunks) {
    stats.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(chunk)));
  }

  Stats result;
  for (auto& stat : stats) {
    result += stat.get();
  }
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
