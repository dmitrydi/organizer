/*
 * database.cpp
 *
 *  Created on: 29 мая 2020 г.
 *      Author: Dmitry_Di
 */

#include "database.h"

ostream& operator <<(ostream& os, const pair<Date, string>& entry) {
  os << entry.first << " " << entry.second;
  return os;
}

void Database::Add(const Date& date, const string& event) {
  if (db_[date].emplace(event).second) {
    database[date].push_back(event);
  }
};

void Database::Print(ostream& os) const {
  for (auto de: database) {
    Date d = de.first;
    for (const string& e: de.second) {
      os << d << " " << e << endl;
    }
  }
};

int Database::RemoveIf(function<bool(Date, string)> predicate) {
  int removed = 0;
  map<Date, vector<string>> database_update;
  for (auto& items: database) {
    auto date = items.first;
    auto cmp = [predicate, date](const string& event) { return predicate(date, event); };
    auto it = stable_partition(items.second.begin(), items.second.end(), cmp);
    for (auto e_it = items.second.begin(); e_it != it; e_it++) {
      db_[date].erase(*e_it);
    }
    if(db_[date].size() == 0) {
      db_.erase(date);
    }
    int n_to_del = it - items.second.begin();
    removed += n_to_del;
    if (n_to_del > 0) {
      database_update[date] = vector<string>(it, items.second.end());
    }
  }
  for (auto& upd: database_update) {
    if (upd.second.size() == 0) {
      database.erase(upd.first);
    } else {
      database[upd.first] = upd.second;
    }
  }
  return removed;
};

/*
vector<pair<Date, string>> Database:: FindIf(function<bool(Date, string)> predicate) const {
  vector<pair<Date, string>> ans;
  for (auto& items: database) {
    for (auto& event: items.second) {
      if (predicate(items.first, event)) {
        ans.push_back(make_pair(items.first, event));
      }
    }
  }
  return ans;
};
*/

vector<pair<Date, string>> Database:: FindIf(function<bool(Date, string)> predicate) const {
  vector<pair<Date, string>> ans;
  for (auto items = database.begin(); items != database.end(); items++) {
    for (auto event = (items->second).begin(); event != (items->second).end(); event++) {
      if (predicate(items->first, *event)) {
        ans.push_back(make_pair(items->first, *event));
      }
    }
  }
  return ans;
};


pair<Date, string> Database::Last(const Date& date) const {
  auto it = database.upper_bound(date);
  if (it == database.begin()) {
    throw invalid_argument("");
  }
  --it;
  return make_pair(it->first, (it->second).back());
};




