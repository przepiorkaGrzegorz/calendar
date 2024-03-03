#pragma once
#include "actual_date.hpp"


class Calendar{
public:
    Calendar();
    void print_menu() const;
    void print_date() const;
    void print_frame() const;
    void print_month() const;
    std::array<int, 3> get_date();
    int get_number() const;
    void print_options() const;
    void check_if_number(int &var) const;
    void run_calendar();

private:
    Date date;
};