#include <string>
#include <vector>
using namespace std;

#define UNIQUE_CONCAT(a, b) a ## b
#define UNIQUE_EXPAND(a, b) UNIQUE_CONCAT(a, b)
#define UNIQ_ID UNIQUE_EXPAND(unique, __LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
