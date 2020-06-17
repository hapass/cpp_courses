#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : users_on_page_(MAX_PAGE_COUNT_ + 1, 0)
      , user_pages_(MAX_USER_COUNT_ + 1, -1)
      , user_count_(0) {}

  void Read(int user_id, int page_count) {
    if (user_pages_[user_id] == -1)
    {
      user_count_++;
    }
    else
    {
      users_on_page_[user_pages_[user_id]]--;
    }

    user_pages_[user_id] = page_count;
    users_on_page_[page_count]++;
  }

  double Cheer(int user_id) const {
    if (user_pages_[user_id] == -1) return 0;
    if (user_count_ == 1) return 1;

    int accumulator = 0;
    for (int page = 1; page < user_pages_[user_id]; page++) {
      accumulator += users_on_page_[page];
    }

    return (accumulator * 1.0) / (user_count_ - 1);
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1000;

  vector<int> users_on_page_;
  vector<int> user_pages_;
  int user_count_;

};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
