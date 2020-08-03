#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
  vector<Sentence<Token>> result;
  int i = 0;
  while (true)
  {
    Sentence<Token> sentence;
    while (i < tokens.size() && !tokens[i].IsEndSentencePunctuation())
    {
      sentence.push_back(move(tokens[i]));
      i++;
    }
    while (i < tokens.size() && tokens[i].IsEndSentencePunctuation())
    {
      sentence.push_back(move(tokens[i]));
      i++;
    }
    if (sentence.size() > 0) result.push_back(move(sentence));
    if (i >= tokens.size()) break;
  }
  return result;
}

struct TestToken
{
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const
  {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken &other) const
  {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
  return stream << token.data;
}

void TestSplitting()
{
  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
      vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
      vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
      vector<Sentence<TestToken>>({
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}},
      }));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
