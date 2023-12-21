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
    static const int MIN_YEAR = 1;
    static const int MAX_YEAR = 9999;
    static const int MIN_MONTH = 1;
    static const int MAX_MONTH = 12;
    static const int MIN_DAY = 1;
    static const int MIN_HOUR = 0;
    static const int MAX_HOUR = 23;
    static const int MIN_MINUTE = 0;
    static const int MAX_MINUTE = 59;
    static const int MIN_SECOND = 0;
    static const int MAX_SECOND = 59;

    CheckLowerBound(dt.year, "year"sv, MIN_YEAR);
    CheckUpperBound(dt.year, "year"sv, MAX_YEAR);
    CheckLowerBound(dt.month, "month"sv, MIN_MONTH);
    CheckUpperBound(dt.month, "month"sv, MAX_MONTH);
    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    CheckLowerBound(dt.day, "day"sv, MIN_DAY);
    CheckUpperBound(dt.day, "day"sv, month_lengths[dt.month - 1]);
    CheckLowerBound(dt.hour, "hour"sv, MIN_HOUR);
    CheckUpperBound(dt.hour, "hour"sv, MAX_HOUR);
    CheckLowerBound(dt.minute, "minute"sv, MIN_MINUTE);
    CheckUpperBound(dt.minute, "minute"sv, MAX_MINUTE);
    CheckLowerBound(dt.second, "second"sv, MIN_SECOND);
    CheckUpperBound(dt.second, "second"sv, MAX_SECOND);
}