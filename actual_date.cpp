#include <iostream>
#include <ctime>
#include "actual_date.hpp"

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


Date::Date(){}

bool Date::get_actual_web_date(){
    namespace asio = boost::asio;
    namespace beast = boost::beast;

    try{
        asio::io_context io_context;
        std::string host = "worldtimeapi.org";
        std::string target = "/api/timezone/Europe/Warsaw";

        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::socket socket(io_context);
        asio::connect(socket, resolver.resolve(host, "http"));

        beast::http::request<beast::http::string_body> request(beast::http::verb::get, target, 11);
        request.set(beast::http::field::host, host);
        request.set(beast::http::field::user_agent, "Boost HTTP/1.1");

        beast::http::write(socket, request);
        beast::flat_buffer buffer;

        beast::http::response<beast::http::string_body> response;
        beast::http::read(socket, buffer, response);

        if(response.result() == beast::http::status::ok){
            boost::property_tree::ptree pt;
            std::istringstream response_stream(response.body());
            boost::property_tree::read_json(response_stream, pt);

            std::string datetime = pt.get<std::string>("datetime");

            day = std::stoi(datetime.substr(8, 2));
            month = std::stoi(datetime.substr(5, 2));
            year = std::stoi(datetime.substr(0, 4));
        }
        else
            std::cerr << "HTTP response error: " << response.result_int() 
                << " " << response.reason() << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void Date::get_actual_system_date(){
    std::time_t t = std::time(NULL);
    std::tm* now = std::localtime(&t);

    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
}

std::string Date::set_web_date(){
    if(get_actual_web_date())
        return std::string("*Web date (worldtimeapi.org)\n");
    else{
        get_actual_system_date();
        return std::string("*Could not connect to web service. \n*System date\n");
    }
}

std::string Date::set_system_date(){
    get_actual_system_date();
    return std::string("*System date\n");
}

bool Date::set_given_date(const int given_day, const int given_month, const int given_year){
    if(given_year < 1582){
        system("clear");
        printf("\nInvalid year\n");
        return false;
    }

    if(given_month < 1 || given_month > 12){
        system("clear");
        printf("\nInvalid month\n");
        return false;
    }

    Days days_struct;
    int number_of_days_in_month = days_struct.days_in_month[given_month];
    if(month == 2){
        if(check_leap_year(year))
            number_of_days_in_month = 29;
    }

    if(given_day < 1 || given_day > number_of_days_in_month + 1){
        system("clear");
        printf("\nInvalid day\n");
        return false;
    }

    day = given_day;
    month = given_month;
    year = given_year;
    return true;
}

int Date::get_day() const{
    return day;
}

int Date::get_month() const{
    return month;
}

int Date::get_year() const{
    return year;
}

int Date::day_of_week() const{
    /*
    week_day = 0         Sunday
    week_day = 1         Monday
    week_day = 2         Tuesday
    week_day = 3         Wednesday
    week_day = 4         Thursday
    week_day = 5         Friday
    week_day = 6         Saturday
    */
 
    int week_day;
    int day_tmp = 1;
    int month_tmp = month;
    int year_tmp = year;

    if(month_tmp < 3){
        month_tmp += 10;
        --year_tmp;
    }
    else
        month_tmp -= 2;

    week_day = (day_tmp + (13*month_tmp - 1)/5 + year_tmp%100 + (year_tmp%100)/4 + 
        (year_tmp/100)/4 - 2*(year_tmp/100)) % 7;

    return (week_day < 0) ? week_day + 7 : week_day;
}

bool Date::check_leap_year(const int year) const{
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? true : false;
}