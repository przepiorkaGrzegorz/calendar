#pragma once
#include <string>
#include <map>


struct Days{
    std::map<int, int> days_in_month = {{1, 31},
                                        {2, 28},
                                        {3, 31},
                                        {4, 30},
                                        {5, 31},
                                        {6, 30},
                                        {7, 31},
                                        {8, 31},
                                        {9, 30},
                                        {10, 31},
                                        {11, 30},
                                        {12, 31}};
};

struct Months{
    std::map<int, std::string> months = {{1, "January"},
                                        {2, "February"},
                                        {3, "March"},
                                        {4, "April"},
                                        {5, "May"},
                                        {6, "June"},
                                        {7, "July"},
                                        {8, "August"},
                                        {9, "September"},
                                        {10, "October"},
                                        {11, "November"},
                                        {12, "December"}};
};


class Date{
public:
    Date();
    bool get_actual_web_date();
    void get_actual_system_date();
    std::string set_web_date();
    std::string set_system_date();
    bool set_given_date(const int given_day, const int given_month, const int given_year);
    int get_day() const;
    int get_month() const;
    int get_year() const;
    int day_of_week() const; // Zeller's algorithm
    bool check_leap_year(const int year) const;

private:
    int day, month, year;
};