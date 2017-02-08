#ifndef FREQ_FREQUENCY_H
#define FREQ_FREQUENCY_H
#include <string>
#include <cstring>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#define N_MINUTE 60
#define N_HOUR 24
#define N_DAY_OF_MONTH 31
#define N_MONTH 12
#define N_DAY_OF_WEEK 7

#define NORMAL_TYPE 0
#define OFFSET_1_TYPE 1

#define INIT_VALUE 1
/*
 *   minute
 *   heure
 *   jour du mois
 *   mois
 *   jour de la semaine
 *
 */
class Frequency {
    char* minutes;
    char* hours;
    char* days_of_month;
    char* months;
    char* days_of_week;

    std::string number_to_string(char* tab,char length,char type);
    void setup();
    char* parser(std::string expr,char size);
public:
    Frequency(){
        setup();
    }
    Frequency(std::string freq){
        std::string buffer;
        std::stringstream ss(freq);
        std::vector<std::string> tokens;
        while (std::getline(ss, buffer, ' '))
            tokens.push_back(buffer);

        if(tokens.size() == 5){
            minutes         = parser(tokens[0],N_MINUTE);
            hours           = parser(tokens[1],N_HOUR);
            days_of_month   = parser(tokens[2],N_DAY_OF_MONTH);
            months          = parser(tokens[3],N_MONTH);
            days_of_week    = parser(tokens[4],N_DAY_OF_WEEK);
        }
    }
    void setMinutes(std::string str){
        delete(minutes);
        minutes = parser(str,N_MINUTE);
    }
    void setHours(std::string str){
        delete(hours);
        hours = parser(str,N_HOUR);
    }
    void setDaysOfMonth(std::string str){
        delete(days_of_month);
        days_of_month = parser(str,N_DAY_OF_MONTH);
    }
    void setMonths(std::string str){
        delete(months);
        months = parser(str,N_MONTH);
    }
    void setDaysOfWeek(std::string str){
        delete(days_of_week);
        days_of_week = parser(str,N_DAY_OF_WEEK);
    }
    Frequency& operator=(const Frequency& target);
    bool contains(char min,char hour,char dom,char month,char dow);
    bool isNow();
    bool since(time_t t);
    std::string toString();
    friend std::ostream& operator<<(std::ostream&,Frequency&);
};

#endif //FREQ_FREQUENCY_H
