#include "Frequency.h"
#include <ctime>
using namespace std;

void Frequency::setup(){
    minutes = new char [N_MINUTE];
    memset(minutes, INIT_VALUE, N_MINUTE);

    hours = new char [N_HOUR];
    memset(hours, INIT_VALUE, N_HOUR);

    days_of_month = new char[N_DAY_OF_MONTH];
    memset(days_of_month, INIT_VALUE, N_DAY_OF_MONTH);

    months = new char[N_MONTH];
    memset(months, INIT_VALUE, N_MONTH);

    days_of_week = new char[N_DAY_OF_WEEK];
    memset(days_of_week, INIT_VALUE, N_DAY_OF_WEEK);
}
char* Frequency::parser(string expr,char size){
    char* tab = new char[size];
    memset(tab, 0, size);

    string part;
    string buffer;
    stringstream ss_expr(expr);

    while (getline(ss_expr, part, ',')){
        if(part.find_first_of('-') == string::npos){
            if(part.compare("*")==0){
                for(int i=0;i<size;i++)
                    tab[i]=1;
                break;
            }
            else{
                int index = stoi(part);
                tab[index]=1;
            }
        }
        else{
            char begin  = -1;
            char end    = -1;
            stringstream ss_part(part);
            while (getline(ss_part, buffer, '-')) {
                if (begin == -1)
                    begin = stoi(buffer);
                else
                    end = stoi(buffer);
            }
            for(int k=begin;k<=end;k++)
                tab[k]=1;
        }
    }

    return tab;
}

string Frequency::number_to_string(char* tab,char length,char type){
    string str = "";
    char empty  =  1;
    char begin  = -1;
    char end    = -1;
    for(char i=0;i<length;i++){
        if(tab[i]==1){
            if(begin == -1)
                begin = i;
            end = i;
        } else{
            if(begin != -1){
                if(!empty)
                    str+=",";

                if(end == begin) {
                    if (type == OFFSET_1_TYPE)
                        str += to_string(begin+1);
                    else
                        str += to_string(begin);
                }else {
                    if (type == OFFSET_1_TYPE)
                        str += to_string(begin+1) + "-" + to_string(end+1);
                    else
                        str += to_string(begin) + "-" + to_string(end);

                }
                empty   =  0;
                begin   = -1;
                end     = -1;
            }
        }
    }
    if(end-begin==length-1)
        str += "*";
    else if(empty)
        str += "0";
    return str;
}
string Frequency::toString(){
    string freq = number_to_string(minutes,N_MINUTE,NORMAL_TYPE)+" ";
    freq += number_to_string(hours,N_HOUR,NORMAL_TYPE)+" ";
    freq += number_to_string(days_of_month,N_DAY_OF_MONTH,OFFSET_1_TYPE)+" ";
    freq += number_to_string(months,N_MONTH,NORMAL_TYPE)+" ";
    freq += number_to_string(days_of_week,N_DAY_OF_WEEK,NORMAL_TYPE);
    return freq;
}
Frequency& Frequency::operator=(const Frequency& src){
    if(this != &src){
        for(int i=0;i<N_MINUTE;i++)
            minutes[i] = src.minutes[i];

        for(int i=0;i<N_HOUR;i++)
            hours[i] = src.hours[i];

        for(int i=0;i<N_DAY_OF_MONTH;i++)
            days_of_month[i] = src.days_of_month[i];

        for(int i=0;i<N_MONTH;i++)
            months[i] = src.months[i];

        for(int i=0;i<N_DAY_OF_WEEK;i++)
            days_of_week[i] = src.days_of_week[i];
    }
    return *this;
}
bool Frequency::contains(char min,char hour,char dom,char month,char dow){
    //TODO tester les arguments
    return minutes[min] && hours[hour] && days_of_month[dom-1] && months[month-1] && days_of_week[dow];
}
bool Frequency::isNow(){
    time_t t = time(0);
    tm * now = localtime(&t);
    cout << now->tm_min << " " << now->tm_hour << " " << now->tm_mday << " " << now->tm_mon << " " << now->tm_wday << endl;
    return contains(now->tm_min,now->tm_hour,now->tm_mday,now->tm_mon,now->tm_wday);
}
bool Frequency::since(time_t t){
    time_t now = time(0);
    tm * date;
    do{
        if(t>now)
            return 0;
        date = localtime(&t);
        t+=60;

    }while(!contains(date->tm_min,date->tm_hour,date->tm_mday,date->tm_mon,date->tm_wday));
    char* dt = asctime(date);
    cout << "Date de la premiere frequence ratee: "<< dt << endl;
    return 1;
}

ostream& operator<<(ostream &o , Frequency &f){
    return o << f.toString();
}
