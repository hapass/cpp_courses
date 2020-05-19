#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    int i = 0;
    if (i == international_number.size()) throw invalid_argument("empty string");
    if (international_number[i++] != '+') throw invalid_argument("country code must start with +");

    ostringstream country_code_stream;
    while (i < international_number.size() && international_number[i] != '-') {
        country_code_stream << international_number[i];
        i++;
    }

    country_code_ = country_code_stream.str();
    if (country_code_ == "") throw invalid_argument("country code is empty");

    if (i == international_number.size()) throw invalid_argument("no city code");
    if (international_number[i++] != '-') throw invalid_argument("city code must start with -");

    ostringstream city_code_stream;
    while (i < international_number.size() && international_number[i] != '-') {
        city_code_stream << international_number[i];
        i++;
    }

    city_code_ = city_code_stream.str();
    if (city_code_ == "") throw invalid_argument("city code is empty");

    if (i == international_number.size()) throw invalid_argument("no local number");
    if (international_number[i++] != '-') throw invalid_argument("local number must start with -");

    ostringstream local_number_stream;
    while (i < international_number.size()) {
        local_number_stream << international_number[i];
        i++;
    }

    local_number_ = local_number_stream.str();
    if (local_number_ == "") throw invalid_argument("local number is empty");
}

string PhoneNumber::GetCountryCode() const { return country_code_; }
string PhoneNumber::GetCityCode() const { return city_code_; }
string PhoneNumber::GetLocalNumber() const { return local_number_; }
string PhoneNumber::GetInternationalNumber() const {
    ostringstream oss;
    oss << "+" << GetCountryCode() << "-" << GetCityCode() << "-" << GetLocalNumber();
    return oss.str();
}