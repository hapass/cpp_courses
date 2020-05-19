#include "test_runner.h"
#include "phone_number.h"

void TestPhoneNumberPositive(const string& number, const string& country, const string& city, const string& local) {
    PhoneNumber n(number);
    AssertEqual(n.GetCountryCode(), country, number + " country code check");
    AssertEqual(n.GetCityCode(), city, number + " city code");
    AssertEqual(n.GetLocalNumber(), local, number + " city code");
    AssertEqual(n.GetInternationalNumber(), number, number + " international");
}

void TestPhoneNumberThrows(const string& number) {
    bool success = false;
    try {
        PhoneNumber n(number);
    } catch (invalid_argument& e) {
        success = true;
    } catch (exception& e) {
        success = false;
    }
    Assert(success, number + " throws invalid_argument");
}

void TestPhoneNumberPositives() {
    TestPhoneNumberPositive("+7-495-111-22-33", "7", "495", "111-22-33");
    TestPhoneNumberPositive("+a-495-111-22-33", "a", "495", "111-22-33");
    TestPhoneNumberPositive("+-7-495-111-22-33", "", "7", "495-111-22-33");
    TestPhoneNumberPositive("+7--111-22-33", "7", "", "111-22-33");
    TestPhoneNumberPositive("+7+495-111-22-33", "7+495", "111", "22-33");
    TestPhoneNumberPositive("+7-abc-111-22-33", "7", "abc", "111-22-33");
    TestPhoneNumberPositive("+abc-495-111-22-33", "abc", "495", "111-22-33");
    TestPhoneNumberPositive("+7-495-1112233", "7", "495", "1112233");
    TestPhoneNumberPositive("+323-22-460002", "323", "22", "460002");
    TestPhoneNumberPositive("+1-2-coursera-cpp", "1", "2", "coursera-cpp");
    TestPhoneNumberPositive("+7-1233-", "7", "1233", "");
}

void TestPhoneNumberNegatives() {
    TestPhoneNumberThrows("");
    TestPhoneNumberThrows("+");
    TestPhoneNumberThrows("+1-");
    TestPhoneNumberThrows("+7-1233");
    TestPhoneNumberThrows("1-2-333");
}

int main() {
    TestRunner r;
    r.RunTest(TestPhoneNumberPositives, "TestPhoneNumberPositives");
    r.RunTest(TestPhoneNumberNegatives, "TestPhoneNumberThrows");
    return 0;
}