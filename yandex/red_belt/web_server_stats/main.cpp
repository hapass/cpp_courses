#include "test_runner.h"
#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>
using namespace std;

Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    const HttpRequest req = ParseRequest(line);
    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}

void TestRequestParser() {
  {
    const string input = "   GET / HTTP/1.1   ";
    HttpRequest request = ParseRequest(input);
    ASSERT_EQUAL(request.method, "GET");
    ASSERT_EQUAL(request.uri, "/");
    ASSERT_EQUAL(request.protocol, "HTTP/1.1");
  }

  {
    string result;
    try
    {
      const string input = "   GET/ HTTP/1.1   ";
      ParseRequest(input);
    }
    catch(const invalid_argument& e)
    {
      result = e.what();
    }
    ASSERT_EQUAL(result, "only one space in request header");
  }

  {
    string result;
    try
    {
      const string input = "   GET/HTTP/1.1   ";
      ParseRequest(input);
    }
    catch(const invalid_argument& e)
    {
      result = e.what();
    }
    ASSERT_EQUAL(result, "no spaces in request header");
  }

  {
    const string input = "   hea   der   ";
    HttpRequest request = ParseRequest(input);
    ASSERT_EQUAL(request.method, "hea");
    ASSERT_EQUAL(request.uri, "");
    ASSERT_EQUAL(request.protocol, " der");
  }
}

void TestBasic() {
  const string input =
    R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

  const map<string_view, int> expected_method_count = {
    {"GET", 8},
    {"PUT", 1},
    {"POST", 4},
    {"DELETE", 1},
    {"UNKNOWN", 1},
  };
  const map<string_view, int> expected_url_count = {
    {"/", 4},
    {"/order", 2},
    {"/product", 5},
    {"/basket", 1},
    {"/help", 1},
    {"unknown", 2},
  };

  istringstream is(input);
  const Stats stats = ServeRequests(is);

  ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() {
  // Методы GetMethodStats и GetUriStats должны возвращать словари
  // с полным набором ключей, даже если какой-то из них не встречался

  const map<string_view, int> expected_method_count = {
    {"GET", 0},
    {"PUT", 0},
    {"POST", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0},
  };
  const map<string_view, int> expected_url_count = {
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0},
  };
  const Stats default_constructed;

  ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRequestParser);
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestAbsentParts);
}
