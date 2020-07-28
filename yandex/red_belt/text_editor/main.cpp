#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
  Editor() {
    cursor_position_ = chars_.end();
  }

  void Left() {
    log("left");
    if (cursor_position_ != chars_.begin()) cursor_position_--;
  }

  void Right() {
    log("right");
    if (cursor_position_ != chars_.end()) cursor_position_++;
  }

  void Insert(char token) {
    cursor_position_ = next(chars_.insert(cursor_position_, token));
    log("inserted " + string(1, token));
  }

  void Cut(size_t tokens = 1) {
    log("cut", tokens);
    buffer_.clear();
    auto begin = cursor_position_;
    cursor_position_ = SelectionEnd(tokens);
    buffer_.splice(buffer_.begin(), chars_, begin, cursor_position_);
  }

  void Copy(size_t tokens = 1) {
    log("copy", tokens);
    buffer_.clear();
    buffer_.insert(buffer_.end(), cursor_position_, SelectionEnd(tokens));
  }

  void Paste() {
    log("paste");
    chars_.insert(cursor_position_, buffer_.begin(), buffer_.end());
  }

  string GetText() const {
    return string(chars_.begin(), chars_.end());
  }

private:
  void log(const string& message, size_t selected = 0) const {
    cout << message;

    if (selected > 0) {
      cout << "|Selected: " << string(cursor_position_, SelectionEnd(selected));
    }

    if (buffer_.begin() != buffer_.end()) {
      cout << "|Buffer: " << string(buffer_.begin(), buffer_.end());
    }

    if (chars_.begin() != chars_.end()) cout << "|Text " << GetText();
    cout << "|Cursor " << (cursor_position_ != chars_.end() ? *cursor_position_ : '$');

    cout << endl;
  }

  list<char>::iterator SelectionEnd(size_t selected_elements) const {
    auto selection_end = cursor_position_;
    while (selected_elements != 0 && selection_end != chars_.end()) {
     selection_end++;
     selected_elements--;
    }
    return selection_end;
  }

  list<char>::iterator cursor_position_;
  list<char> chars_;
  list<char> buffer_;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");

    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }

    TypeText(editor, ", ");

    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}