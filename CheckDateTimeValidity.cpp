#include <string_view>

void CheckLowerBound(int value, std::string_view name, int border) {
    if (value < border) {
        throw domain_error(name + " is too small"s);
    }
}

void CheckUpperBound(int value, std::string_view name, int border) {
    if (value > border) {
        throw domain_error(name + " is too big"s);
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    using namespace std::literals;
    CheckLowerBound(dt.year, "year"sv, 1);
    CheckUpperBound(dt.year, "year"sv, 9999);
    CheckLowerBound(dt.month, "month"sv, 1);
    CheckUpperBound(dt.month, "month"sv, 12);
    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    CheckLowerBound(dt.day, "day"sv, 1);
    CheckUpperBound(dt.day, "day"sv, month_lengths[dt.month - 1]);
    CheckLowerBound(dt.hour, "hour"sv, 0);
    CheckUpperBound(dt.hour, "hour"sv, 23);
    CheckLowerBound(dt.minute, "minute"sv, 0);
    CheckUpperBound(dt.minute, "minute"sv, 59);
    CheckLowerBound(dt.second, "second"sv, 0);
    CheckUpperBound(dt.second, "second"sv, 59);
}