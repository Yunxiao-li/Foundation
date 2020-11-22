// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "../LogFrame/my_log.h"

const char TESTPATH[20] = "log_test.txt";
const char TESTSOURCE[20] = "project_text";
const int  TESTID = 2001;
#define LOG_INFO_TEST     LOG_INFO(TESTPATH, TESTSOURCE, TESTID)
#define LOG_WARNING_TEST  LOG_WARNING(TESTPATH, TESTSOURCE, TESTID)
#define LOG_ERROR_TEST    LOG_ERROR(TESTPATH, TESTSOURCE, TESTID)

#pragma comment(lib, "Log.lib")
void Testlog()
{
    LOG_INFO_TEST << 1111 << " " << -10 << " hhhh";
    LOG_WARNING_TEST << "222" << " " << "aa";
    LOG_ERROR_TEST << "3333" << " " << "999" << " " << "shfoew";
}
int main()
{
    LOG_INIT;
    LOG_INFO_TEST << 1;
    Testlog();
    LOG_SHUTDOWN;
    std::cout << "Hello World!\n";
}

