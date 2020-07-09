#include "test_runner.h"
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
    string source_copy(source);
    string target_copy(target);

    words_.insert(source_copy);
    words_.insert(target_copy);

    const string& source_ref = *words_.find(source_copy);
    const string& target_ref = *words_.find(target_copy);

    forward_translations_[source_ref] = target_ref;
    backward_translations_[target_ref] = source_ref;
  }

  string_view TranslateForward(string_view source) const {
    return Translate(source, forward_translations_);
  }

  string_view TranslateBackward(string_view target) const {
    return Translate(target, backward_translations_);
  }

private:
  string_view Translate(string_view word, const map<string_view, string_view>& translations) const {
    if (translations.count(word) == 0) {
      return empty_;
    }
    return translations.at(word);
  }

  const string empty_;
  set<string> words_;
  map<string_view, string_view> forward_translations_;
  map<string_view, string_view> backward_translations_;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
