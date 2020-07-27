#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
  Editor() {
    cout << "created editor" << endl;
    cursor_position_ = chars_.begin();
  }

  void Left() {
    cout << "left" << endl;
    if (cursor_position_ != chars_.begin()) cursor_position_--;
  }

  void Right() {
    cout << "right" << endl;
    if (next(cursor_position_) != chars_.end()) cursor_position_++;
  }

  void Insert(char token) {
    cout << "insert " << token << endl;
    chars_.insert(cursor_position_, token);
    cursor_position_++;
  }

  void Cut(size_t tokens = 1) {
    cout << "cut " << string(SelectionBegin(), SelectionEnd(tokens)) << endl;
    buffer_.clear();
    buffer_.splice(buffer_.begin(), chars_, SelectionBegin(), SelectionEnd(tokens));
  }

  void Copy(size_t tokens = 1) {
    cout << "copy " << string(SelectionBegin(), SelectionEnd(tokens)) << endl;
    buffer_.clear();
    buffer_.insert(buffer_.end(), SelectionBegin(), SelectionEnd(tokens));
  }

  void Paste() {
    cout << "paste " << string(buffer_.begin(), buffer_.end()) << endl;
    chars_.insert(next(cursor_position_), buffer_.begin(), buffer_.end());
  }

  string GetText() const {
    cout << "get text" << endl;
    return string(chars_.begin(), chars_.end());
  }

private:
  std::list<char>::iterator SelectionBegin() const {
    return cursor_position_;
  }

  std::list<char>::iterator SelectionEnd(size_t selected_elements) const {
    auto selection_end = cursor_position_;
    while (selected_elements != 0 && selection_end != chars_.end()) {
     selection_end++;
     selected_elements--;
    }
    return selection_end;
  }

  std::list<char>::iterator cursor_position_;
  std::list<char> chars_;
  std::list<char> buffer_;
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