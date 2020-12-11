#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
using std::string;
using std::stringstream;
using std::ostream;

inline bool isLeapYear(int year)
{
    return (year%4 == 0 && year%100 != 0) || (year%400 == 0);
}

class Date
{
private:
    unsigned int year, month, day;
public:
    // constructor
    Date()
    {
        year = month = day = 1;
    }
    Date(unsigned int year, unsigned int month, unsigned int day)
    {
        if(!setDate(year, month, day))
            Date();
        this->year  = year;
        this->month = month;
        this->day   = day;
    }
    bool setDate(int y, int m, int d)
    {
        if(m<1 || m>12) return false;
        if(d<1 || d>31) return false;
        switch(m)
        {
            case 2: if(isLeapYear(y))
                    {
                        if(d>29) return false;
                    }
                    else
                        if(d>28) return false;
                    break;
            case 4:
            case 6:
            case 9:
            case 11: if(d>30) return false;
        }
        return true;
    }
    void setDate(void)
    {
        struct tm *tm;
        time_t sec; std::time(&sec);
        tm = std::localtime(&sec);

        year  = (unsigned int)tm->tm_year + 1900;
        month = (unsigned int)tm->tm_mon + 1;
        day   = (unsigned int)tm->tm_mday;
    }
    // destructor
    virtual ~Date(){}
    // getter
    unsigned int getYear(void)  const { return year; }
    unsigned int getMonth(void) const { return month; }
    unsigned int getDay(void)   const { return day; }
    // setter
    void setYear(unsigned int y)  { year = y; }
    void setMonth(unsigned int m) { month = m; }
    void setDay(unsigned int d)   { day = d; }
    // repr
    string asString(void) const
    {
        stringstream ss;
        ss << std::setw(4) << std::setfill('0') << year  << "/"
           << std::setw(2) << std::setfill('0') << month << "/"
           << std::setw(2) << std::setfill('0') << day;
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, const Date& d)
    {
        os << d.asString();
        return os;
    }
    // comparison
    bool operator==(const Date& d)
    {
        return (year == d.year && month == d.month && day == d.day);
    }
    bool operator<(const Date& d)
    {
        if(year != d.year)        return (year < d.year);
        else if(month != d.month) return (month < d.month);
        else                      return (day < d.day);
    }
    bool operator>(const Date& d)
    {
        if(year != d.year)        return (year > d.year);
        else if(month != d.month) return (month > d.month);
        else                      return (day > d.day);
    }
};

#endif // DATE_H_INCLUDED
