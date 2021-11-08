#pragma once

#include <string>
#include <exception>
#include <iomanip>

class Date {
public:
  Date(const int year, const int month, const int day) :
    _year(year),
    _month(month),
    _day(day) {};
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
private:
  const int _year, _month, _day;
};

Date ParseDate(std::istream& is);

std::ostream& operator <<(std::ostream& os, const Date& date);
bool operator >(const Date& lhs, const Date& rhs);
bool operator <(const Date& lhs, const Date& rhs);
bool operator !=(const Date& lhs, const Date& rhs);
bool operator ==(const Date& lhs, const Date& rhs);
bool operator >=(const Date& lhs, const Date& rhs);
bool operator <=(const Date& lhs, const Date& rhs);

