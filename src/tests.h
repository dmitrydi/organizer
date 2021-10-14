#pragma once

#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

using namespace std;

string ParseEvent(istream& is);

void TestParseDate();
void TestAddEvents();
void TestFindIf();


