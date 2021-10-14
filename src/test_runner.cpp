/*
 * test_runner.cpp
 *
 *  Created on: 28 ��� 2020 �.
 *      Author: Dmitry_Di
 */
#include "test_runner.h"

TestRunner::~TestRunner() {
   if (fail_count > 0) {
     cerr << fail_count << " unit tests failed. Terminate" << endl;
     exit(1);
   }
}
