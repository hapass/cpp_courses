#include "test_runner.h"
#include "phone_number.h"

/* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
void TestPhoneNumberValidation() {
    {
        PhoneNumber number("+7-495-111-22-33");
        AssertEqual(number.GetCountryCode(), "7", "+7-495-111-22-33 country code check");
        AssertEqual(number.GetCityCode(), "495", "+7-495-111-22-33 city code");
        AssertEqual(number.GetLocalNumber(), "111-22-33", "+7-495-111-22-33 city code");
    }
}

int main() {
    TestRunner r;
    r.RunTest(TestPhoneNumberValidation, "TestPhoneNumberValidation");
    return 0;
}