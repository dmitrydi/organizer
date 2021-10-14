#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>
#include "date.h"
#include "node.h"

using namespace std;

class Database {
public:
  void Add(const Date& date, const string& event);

  void Print(ostream& os) const;

  int RemoveIf(function<bool(Date, string)> predicate);

  vector<pair<Date, string>> FindIf(function<bool(Date, string)> predicate) const;

  pair<Date, string> Last(const Date& date) const;

  map<Date, vector<string>> GetDatabase() const {
    return database;
  }
private:
  map<Date, vector<string>> database;
  map<Date, set<string>> db_;
};

ostream& operator <<(ostream& os, const pair<Date, string>& entry);
