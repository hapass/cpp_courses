#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    ostringstream oss;
    istringstream iss(international_number);

    iss.ignore(1);

    uint32_t country_code;
    iss >> country_code;
    oss << country_code;
    country_code_ = oss.str();

    iss.ignore(1);

    uint32_t city_code;
    iss >> city_code;
    oss.str("");
    oss << city_code;
    city_code_ = oss.str();

    iss.ignore(1);

    iss >> local_number_;
}

string PhoneNumber::GetCountryCode() const { return country_code_; }
string PhoneNumber::GetCityCode() const { return city_code_; }
string PhoneNumber::GetLocalNumber() const { return local_number_; }
string PhoneNumber::GetInternationalNumber() const {
    ostringstream oss;
    oss << "+" << GetCountryCode() << "-" << GetCityCode() << "-" << GetLocalNumber();
    return oss.str();
}