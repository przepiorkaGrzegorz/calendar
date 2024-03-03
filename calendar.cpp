#include <iostream>
#include <array>
#include <climits>
#include "calendar.hpp"


Calendar::Calendar(){}

void Calendar::print_menu() const{
    system("clear");
    printf("\n========= CALENDAR =========\n\n");
    printf("1. Show actual date (Web)\n"
        "2. Show actual date (System)\n"
        "3. Show given date\n"
        "4. Quit\n");
}

void Calendar::print_date() const{
    Months months_struct;
    system("clear");
    printf("\n\t %d %s %d\n\n", 
        date.get_day(), months_struct.months[date.get_month()].c_str(), date.get_year());
}

void Calendar::print_frame() const{
    printf("\033[31mSUN\033[0m  MON  TUE  WED  THU  \033[36mFRI\033[0m  \033[36mSAT\033[0m\n"
        "=================================\n");
}

void Calendar::print_month() const{
    Days days_struct;
    int number_of_days_in_month = days_struct.days_in_month[date.get_month()];
    int starting_day = date.day_of_week();
    int day_counter = 1;
    int k;

    if(date.get_month() == 2){
        if(date.check_leap_year(date.get_year()))
            number_of_days_in_month = 29;
    }

    for(k = 0; k != starting_day; ++k)
        printf("     ");

    for(int i = 0; i != number_of_days_in_month; ++i){
        if(day_counter == date.get_day())
            printf("\033[32m%2d\033[0m   ", day_counter++);
        else if(0 == k)
            printf("\033[31m%2d\033[0m   ", day_counter++);
        else if(5 == k || 6 == k)
            printf("\033[36m%2d\033[0m   ", day_counter++);
        else
            printf("%2d   ", day_counter++);

        if(6 == k++){
            printf("\n");
            k = 0;
        }
    }
    printf("\n");
}

std::array<int, 3> Calendar::get_date(){
    printf("Pick your date (day, month, year)\n");
    printf("\nDay [1 - 31]: ");
    int day = get_number();
    printf("\nMonth [1 - 12]: ");
    int month = get_number();
    printf("\nYear [1583 - ]: ");
    int year = get_number();

    return std::array<int, 3>{day, month, year};
}

int Calendar::get_number() const{
    int var;
    check_if_number(var);
    return var;
}

void Calendar::print_options() const{
    printf("\n1. Get back"
        "\n2. Quit"
        "\n\nPick an option [1 - 2]: ");
}

void Calendar::check_if_number(int &var) const{
    while(!(std::cin >> var)){
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        printf("\x1b[1A\x1b[2K");
        printf("Invalid input! Try again: ");
    }
}

void Calendar::run_calendar(){
    int choice_4, choice_2;
    bool run = true;

    print_menu();
    printf("\nPick an option [1 - 4]: ");
    check_if_number(choice_4);

    while(run){
        main_menu:
        bool flag = false;
        
        switch(choice_4){
            case 1: { // Show_actual_date (Web)
                std::string str = date.set_web_date();
                print_date();
                print_frame();
                print_month();
                printf("%s", str.c_str());
                print_options();
                check_if_number(choice_2);
            }
                menu_web:
                switch(choice_2){
                    case 1: // 1. Get back
                        print_menu();
                        printf("\nPick an option [1 - 4]: ");
                        check_if_number(choice_4);
                        goto main_menu;

                    case 2: // 2. Quit
                        run = false;
                        break;

                    default:
                        printf("\x1b[1A\x1b[2K");
                        printf("Invalid input! Try again: ");
                        check_if_number(choice_2);
                        goto menu_web;
                }
                break;

            case 2: { // Show_actual_date (System)
                std::string str = date.set_system_date();
                print_date();
                print_frame();
                print_month();
                printf("%s", str.c_str());
                print_options();
                check_if_number(choice_2);
            }

                menu_system:
                switch(choice_2){
                    case 1: // 1. Get back
                        print_menu();
                        printf("\nPick an option [1 - 4]: ");
                        check_if_number(choice_4);
                        goto main_menu;

                    case 2: // 2. Quit
                        run = false;
                        break;

                    default:
                        printf("\x1b[1A\x1b[2K");
                        printf("Invalid input! Try again: ");
                        check_if_number(choice_2);
                        goto menu_system;
                }
                break;

            case 3: // Show given date
                while(!flag){
                    std::array<int, 3> given_date = get_date();
                    flag = date.set_given_date(given_date[0], given_date[1], given_date[2]);
                }
                print_date();
                print_frame();
                print_month();
                printf("*User date\n");
                print_options();
                check_if_number(choice_2);

                switch(choice_2){
                    case 1: // 1. Get back
                        print_menu();
                        printf("\nPick an option [1 - 4]: ");
                        check_if_number(choice_4);
                        goto main_menu;

                    case 2: // 2. Quit
                        run = false;
                        break;
                        
                    default:
                        printf("\nInvalid input! Pick again [1 - 2]: ");
                        check_if_number(choice_2);
                        break;
                }
                break;

            case 4: // Quit
                run = false;
                break;

            default:
                printf("\x1b[1A\x1b[2K");
                printf("Invalid input! Try again: ");
                check_if_number(choice_4);
                break;
        }
    }
}