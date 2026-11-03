#include "Date.h"
#include <ctime>
#include <sstream>
#include <stdexcept>

static int daysInMonth(int month, int year) {
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return 29;
        else return 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    else return 31;
}

void Date::add_months(int months) {
    month += months;
    while (month > 12) { month -= 12; year++; }
    while (month < 1) { month += 12; year--; }

    // Adjust day to last valid day of the new month
    int maxDay = daysInMonth(month, year);
    if (day > maxDay) day = maxDay;
}

std::string Date::to_string() const {
    std::ostringstream oss;
    oss << year << "-"
        << (month < 10 ? "0" : "") << month << "-"
        << (day < 10 ? "0" : "") << day;
    return oss.str();
}

Date Date::from_string(const std::string& str) {
    Date d{};
    char delimiter;
    std::stringstream ss(str);
    ss >> d.year >> delimiter >> d.month >> delimiter >> d.day;
    return d;
}

Date Date::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return {ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year};
}