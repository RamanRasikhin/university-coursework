#ifndef DATE_H
#define DATE_H

#include <string>

struct Date {
    int day;
    int month;
    int year;

    void add_months(int months);
    std::string to_string() const;
    static Date from_string(const std::string& str);
    static Date getCurrentDate();
};

#endif