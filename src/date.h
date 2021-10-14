#pragma once

#include <string>
#include <exception>
#include <iomanip>

using namespace std;

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

Date ParseDate(istream& is);

ostream& operator <<(ostream& os, const Date& date);
bool operator >(const Date& lhs, const Date& rhs);
bool operator <(const Date& lhs, const Date& rhs);
bool operator !=(const Date& lhs, const Date& rhs);
bool operator ==(const Date& lhs, const Date& rhs);
bool operator >=(const Date& lhs, const Date& rhs);
bool operator <=(const Date& lhs, const Date& rhs);

