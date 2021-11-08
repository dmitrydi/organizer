#include "date.h"

using namespace std;

int Date::GetYear() const {
  return _year;
};

int Date::GetMonth() const {
  return _month;
};

int Date::GetDay() const {
  return _day;
};

Date ParseDate(istream& is) {
  int year, month, day;
  string syear, smonth, sday;
  if (getline(is, syear, '-')) {
    year = stoi(syear);
  } else {
    throw invalid_argument("invalid year");
  }
  if (getline(is, smonth, '-')) {
    month = stoi(smonth);
  } else {
    throw invalid_argument("invalid month");
  }
  if (getline(is, sday, ' ')) {
    day = stoi(sday);
  } else {
    throw invalid_argument("invalid day");
  }
  return Date(year, month, day);
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() != rhs.GetYear()) {
    return lhs.GetYear() < rhs.GetYear();
  } else {
    if (lhs.GetMonth() != rhs.GetMonth()) {
      return lhs.GetMonth() < rhs.GetMonth();
    } else {
      return lhs.GetDay() < rhs.GetDay();
    }
  }
};

bool operator>(const Date& lhs, const Date& rhs) {
  return (rhs < lhs);
};

bool operator==(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear() &&
      lhs.GetMonth() == rhs.GetMonth() &&
      lhs.GetDay() == rhs.GetDay()) {
    return true;
  } else {
    return false;
  }
};

bool operator !=(const Date& lhs, const Date& rhs) {
  return !(lhs == rhs);
};

bool operator <=(const Date& lhs, const Date& rhs) {
  return (lhs < rhs) || (lhs == rhs);
};

bool operator >=(const Date& lhs, const Date& rhs) {
  return (lhs > rhs) || (lhs == rhs);
};

ostream& operator <<(ostream& os, const Date& date) {
  os << setfill('0');
  os << setw(4) << date.GetYear();
  os << '-';
  os << setw(2) << date.GetMonth();
  os << '-';
  os << setw(2) << date.GetDay();
  return os;
}


