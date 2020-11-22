#pragma once

#define _CRT_SECURE_NO_WARNINGS //disable security error

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "my_log_def.h"


#ifdef BUILD_MY_LOG
#define __SELF
#endif
#include "my_imp_exp.h"

const int WRITE_FILE_MODE_TURNC = 0;        // delete and write file 
const int WRITE_FILE_MODE_APP = 1;          // append file
const int WRITE_FILE_MODE_END = 2;          // close after write file

namespace myspace {

    __IM_EX_FUNC_C void MyLog_Initialize();

    __IM_EX_FUNC_C void MyLog_Shutdown();


    class __IM_EX_CLASS MyLog 
    {
    public:
        MyLog(const char* path, const char *file, const char *func, const int32_t &line, const char *logSource, const int32_t &logId, const char *logLevel);

        ~MyLog();
        MyLog &operator << (const int8_t &val);
        MyLog &operator << (const uint8_t &val);
        MyLog &operator << (const int16_t &val);
        MyLog &operator << (const uint16_t &val);
        MyLog &operator << (const int32_t &val);
        MyLog &operator << (const uint32_t &val);
        MyLog &operator << (const int64_t &val);
        MyLog &operator << (const uint64_t &val);
        MyLog &operator << (const float &val);
        MyLog &operator << (const double &val);
        MyLog &operator << (const bool &val);
        MyLog &operator << (const char *val);

    private:
        // handle case: log << msg1 << msg2, ensure msg lenth if is enough
        bool GetMsgLen(size_t &len);
        template <typename T>
        void FormatPrint(const char* print_type, const T& val);

        Log::MsgInfo m_Msg;
    };
}


#ifndef LOG_INIT
#define LOG_INIT              myspace::MyLog_Initialize()
#endif

#ifndef LOG_SHUTDOWN
#define LOG_SHUTDOWN          myspace::MyLog_Shutdown()
#endif

#ifndef LOG_INFO
#define LOG_INFO(path, sSource, uiLogUID)      myspace::MyLog(path, __FILE__, __FUNCTION__, __LINE__, sSource, uiLogUID, myspace::MY_LOG_INFO)
#endif

#ifndef LOG_WARNING
#define LOG_WARNING(path, sSource, uiLogUID)   myspace::MyLog(path, __FILE__, __FUNCTION__, __LINE__, sSource, uiLogUID, myspace::MY_LOG_WARNING)
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(path, sSource, uiLogUID)     myspace::MyLog(path, __FILE__, __FUNCTION__, __LINE__, sSource, uiLogUID, myspace::MY_LOG_ERROR)
#endif


