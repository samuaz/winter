/**
 * @author AZCONA VARGAS, SAMUEL EDUARDO -
 * samuel@theopencompany.tech/samuaz@gmail.com
 * @YEAR 2019
 */

#include <wintercpp/util/winter_date.h>

#include <ctime>
#include <iostream>
#include <sstream>

using namespace winter;

Date::Date() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  std::stringstream date;

  _year = 1 + ltm->tm_year;
  _month = 1 + ltm->tm_mon;
  _day = ltm->tm_mday;
  _hour = ltm->tm_hour;
  _minute = ltm->tm_min;
  _second = ltm->tm_sec;
}

Date::Date(const std::string &date) {
  sscanf(
      date.c_str(),
      "%4d-%2d-%2d %2d:%2d:%2d",
      &_year,
      &_month,
      &_day,
      &_hour,
      &_minute,
      &_second);
}

Date::Date(int year, int month, int day) :
    _year(year),
    _month(month),
    _day(day) {}

Date::Date(int year, int month, int day, int hour, int minute, int second) :
    _year(year),
    _month(month),
    _day(day),
    _hour(hour),
    _minute(minute),
    _second(second) {}

int Date::year() const {
  return _year;
}

void Date::year(int year) {
  Date::_year = year;
}

int Date::month() const {
  return _month;
}

void Date::month(int month) {
  Date::_month = month;
}

int Date::day() const {
  return _day;
}

void Date::day(int day) {
  Date::_day = day;
}

int Date::hour() const {
  return _hour;
}

void Date::hour(int hour) {
  Date::_hour = hour;
}

int Date::minute() const {
  return _minute;
}

void Date::minute(int minute) {
  Date::_minute = minute;
}

int Date::second() const {
  return _second;
}

void Date::second(int second) {
  Date::_second = second;
}

std::string
Date::toString() const {
  std::stringstream ss;
  std::string sYear(std::to_string(_year));
  std::string sMonth(std::to_string(_month));
  std::string sDay(std::to_string(_day));
  std::string sHour(std::to_string(_hour));
  std::string sMin(std::to_string(_minute));
  std::string sSec(std::to_string(_second));

  std::string *values[] = {&sYear, &sMonth, &sDay, &sHour, &sMin, &sSec};

  for (auto value : values)

    if (value->length() < 2) {
      *value = "0" + *value;
    }

  ss << sYear << '-' << sMonth << "-" << sDay << " " << sHour << ":" << sMin
     << ":" << sSec << std::endl;
  return ss.str();
}

bool Date::operator==(const Date &ref) const {
  return _day == ref._day && _month == ref._month && _year == ref._year
	 && _hour == ref._hour && _minute == ref._minute
	 && _second == ref._second;
}

bool Date::operator!=(const Date &ref) const {
  return !(ref == *this);
}

bool Date::operator<(const Date &rhs) const {
  if (_year < rhs._year)
    return true;
  if (rhs._year < _year)
    return false;
  if (_month < rhs._month)
    return true;
  if (rhs._month < _month)
    return false;
  if (_day < rhs._day)
    return true;
  if (rhs._day < _day)
    return false;
  if (_hour < rhs._hour)
    return true;
  if (rhs._hour < _hour)
    return false;
  if (_minute < rhs._minute)
    return true;
  if (rhs._minute < _minute)
    return false;
  return _second < rhs._second;
}

bool Date::operator>(const Date &rhs) const {
  return rhs < *this;
}

bool Date::operator<=(const Date &rhs) const {
  return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const {
  return !(*this < rhs);
}
