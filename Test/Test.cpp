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
#include <thread>
#include <chrono>
#include <sstream>

const char TESTPATH[20] = "log_test.txt";
const char TESTSOURCE[20] = "project_text";
const int  TESTID = 2001;
#define LOG_INFO_TEST     LOG_INFO(TESTPATH, TESTSOURCE, TESTID)
#define LOG_WARNING_TEST  LOG_WARNING(TESTPATH, TESTSOURCE, TESTID)
#define LOG_ERROR_TEST    LOG_ERROR(TESTPATH, TESTSOURCE, TESTID)

#pragma comment(lib, "Log.lib")

void Testlog()
{
    LOG_INFO_TEST << "this is info ---------------" << " " << -10 << " hhhh";
    LOG_WARNING_TEST << "this is warning ------------" << " " << "aa";
    LOG_ERROR_TEST << "this is error ------------" << " " << "999" << " " << "shfoew";
}

void WriteLog()
{
	int loop = 10;
	while (--loop)
	{
		auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream ss;
		ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %X");
		std::stringstream ssid;
		ssid << std::this_thread::get_id();
		LOG_INFO_TEST << "thread ID: " << ssid.str().c_str() << " Current Time: " << ss.str().c_str();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
}

int main()
{
    LOG_INIT;

	std::thread t1(WriteLog);
	std::thread t2(WriteLog);
	Testlog();
	t1.join();	
	t2.join();
    
    LOG_SHUTDOWN;
}

