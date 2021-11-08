#include "tests.h"

using namespace std;

void TestParseDate() {
  string line = "2017-01-01 2017-1-1 Something";
  istringstream is(line);
  const Date date1 = ParseDate(is);
  const Date date2 = ParseDate(is);
  string next_string;
  getline(is, next_string);
  AssertEqual(date1, Date{2017, 1, 1}, "Test parsing first date");
  AssertEqual(date2, Date{2017, 1, 1}, "Test parsing second date");
  AssertEqual(next_string, "Something", "Test next part of string is preserved");
}

void TestAddEvents() {
  {
    string line = "2017-01-01 Holiday";
    istringstream is(line);
    const Date date = ParseDate(is);
    string event = ParseEvent(is);
    Database db;
    db.Add(date, event);
    AssertEqual(db.GetDatabase()[date], vector<string> {"Holiday"}, "Test Adding one event to one date");
  }
  {
    Database db;
    istringstream line("2017-01-01 Holiday\n2017-01-01 Holiday");
    for (int i = 0; i < 2; i++) {
      Date date = ParseDate(line);
      string event = ParseEvent(line);
      db.Add(date, event);
    }
    Date date{2017, 1, 1};
    AssertEqual(db.GetDatabase()[date], vector<string> {"Holiday"}, "Test Adding two equal events to one date");
  }
  {
      Database db;
      istringstream line("2017-01-01 Holiday\n2017-01-01 Birthday");
      for (int i = 0; i < 2; i++) {
        Date date = ParseDate(line);
        string event = ParseEvent(line);
        db.Add(date, event);
      }
      Date date{2017, 1, 1};
      AssertEqual(db.GetDatabase()[date], vector<string> {"Holiday", "Birthday"}, "Test Adding two different events to one date");
   }
  {
    Database db;
    vector<pair<Date, string>> test_input { {Date{2017,1,1}, "Holiday"},
                                            {Date{2017,1,1}, "Birthday"},
                                            {Date{2017,1,1}, "Holiday"},
                                            {Date{2017,1,2}, "Working day"} };
    for (auto& in: test_input) {
      Date date = in.first;
      string event = in.second;
      db.Add(date, event);
    }
    AssertEqual(db.GetDatabase()[Date{2017,1,1}], vector<string> {"Holiday", "Birthday"}, "1");
    AssertEqual(db.GetDatabase()[Date{2017,1,2}], vector<string> {"Working day"}, "2");
  }
}

void TestFindIf() {
  Database db;
  vector<pair<Date, string>> test_input {
                                          {Date{2017,1,1}, "Holiday"},
                                          {Date{2017,1,1}, "Birthday"},
                                          {Date{2017,1,1}, "Holiday"},
                                          {Date{2017,1,2}, "Working day"},
                                          {Date{2017,1,1}, "Holiday"},
                                          {Date{2017,1,3}, "Holiday"},
                                          {Date{2017,1,3}, "Some event"},
                                        };
  for (auto& in: test_input) {
    Date date = in.first;
    string event = in.second;
    db.Add(date, event);
  }
  {
    istringstream is(R"(date >= 2017-01-01 AND date <= 2017-01-03 AND event == "Holiday")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    vector<pair<Date, string>> result = db.FindIf(predicate);
    vector<pair<Date, string>> expected = {
        {Date{2017,1,1}, "Holiday"},
        {Date{2017,1,3}, "Holiday"}
    };
    AssertEqual(result, expected, "Test 1");
  }
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestParseDate, "Test ParseDate");
  tr.RunTest(TestAddEvents, "Test Add in database");
  tr.RunTest(TestFindIf, "Tst FindIf");
}

