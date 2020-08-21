#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <string_view>
#include <utility>
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
  return ExploreKeyWordsSingleThread(key_words, input);
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
