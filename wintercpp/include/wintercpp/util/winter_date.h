/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#ifndef USER_DATE_H
#define USER_DATE_H

#include <cstdio>
#include <iomanip>
#include <string>

/**
 * @class Date
 * simulate java Date functionality WORK IN PROGRESS
 */
namespace winter {

    class Date {
       public:
        Date();

        explicit Date(const std::string &date);

        Date(int year, int month, int day);

        Date(int year, int month, int day, int hour, int minute, int second);

        int year() const;

        void year(int year);

        int month() const;

        void month(int month);

        int day() const;

        void day(int day);

        int hour() const;

        void hour(int hour);

        int minute() const;

        void minute(int minute);

        int second() const;

        void second(int second);

        bool operator==(const Date &ref) const;

        bool operator!=(const Date &ref) const;

        bool operator<(const Date &rhs) const;

        bool operator>(const Date &rhs) const;

        bool operator<=(const Date &rhs) const;

        bool operator>=(const Date &rhs) const;

        std::string toString() const;

       private:
        int _year = 0;
        int _month = 0;
        int _day = 0;
        int _hour = 0;
        int _minute = 0;
        int _second = 0;
    };

}  // namespace winter
#endif  // USER_DATE_H
