#include "my_log.h"
#include "my_log_def.h"
#include "my_log_task.h"
#include "my_log_queue.h"
#include <fstream>
#include <process.h>
#include <iomanip>

using namespace myspace;
using namespace myspace::Log;

void myspace::MyLog_Initialize()
{
    myspace::LogTask::GetInstance().Start();
}

MyLog::MyLog(const char* path, const char *file, const char *func, const int32_t &line,
             const char *logSource, const int32_t &logId, const char *logLevel) 
{
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    strncpy_s(m_Msg.time, ss.str().c_str(), max_time_string_length-1);
    strncpy_s(m_Msg.file, file, max_file_string_length-1);
    strncpy_s(m_Msg.func, func, max_function_string_length-1);
    strncpy_s(m_Msg.source, logSource, max_log_source-1);
    strncpy_s(m_Msg.level, logLevel, max_log_level-1);
    strncpy_s(m_Msg.path, path, max_file_path_length-1);
    m_Msg.log_id = logId;
    m_Msg.line = line;
    m_Msg.mode = WRITE_FILE_MODE_APP;
    m_Msg.length = 0;
    m_Msg.pid = _getpid();
}

MyLog::~MyLog() 
{   
    myspace::Log::LogQueue::push(m_Msg);
}

MyLog &MyLog::operator << (const int32_t &val) 
{
    FormatPrint("%d", val);
    return *this;
}

MyLog &MyLog::operator << (const int8_t &val) 
{
    FormatPrint("%d", val);
    return *this;
}

MyLog &MyLog::operator << (const uint8_t &val) 
{
    FormatPrint("%u", val);
    return *this;
}

MyLog &MyLog::operator << (const int16_t &val) 
{
    FormatPrint("%d", val);
    return *this;
}

MyLog &MyLog::operator << (const uint16_t &val) 
{
    FormatPrint("%u", val);
    return *this;
}

MyLog &MyLog::operator << (const uint32_t &val) 
{
    FormatPrint("%u", val);
    return *this;
}

MyLog &MyLog::operator << (const int64_t &val) 
{
    FormatPrint("%lld", val);
    return *this;
}

MyLog &MyLog::operator << (const uint64_t &val) 
{
    FormatPrint("%llu", val);
    return *this;
}

MyLog &MyLog::operator << (const bool &val) {
    *this << (val ? "TRUE" : "FALSE");
    return *this;
}

MyLog &MyLog::operator << (const float &val) 
{
    FormatPrint("%f", val);
    return *this;
}

MyLog &MyLog::operator << (const double &val) 
{
    FormatPrint("%lf", val);
    return *this;
}

MyLog &MyLog::operator << (const char *val) 
{
    if(m_Msg.length < (max_message_length - 1) &&  NULL != val) 
    {
        size_t len = strlen(val);
        uint16_t start_point = m_Msg.length;
        // if there is enough space for new message
        if(GetMsgLen(len))
            std::strncpy(&m_Msg.message[start_point], val, len);
    }
    return *this;
}

template <typename T>
void MyLog::FormatPrint(const char* print_type, const T& val)
{
    if (m_Msg.length < (Log::max_message_length - 1))
    {
        char mymsg[Log::max_d_length];
        // msg legth for this operation <<;
        size_t mymsglen = _snprintf(&mymsg[0], Log::max_d_length, print_type, val);
        // previous accumulating msg lengh
        uint16_t start_point = m_Msg.length;
        if (GetMsgLen(mymsglen))
            memcpy(&m_Msg.message[start_point], &mymsg[0], mymsglen);
    }
}

bool MyLog::GetMsgLen(size_t &len) 
{
    // there is free space
    if(m_Msg.length < (max_message_length - 1)) 
    {
        // there is enough space 
        if((m_Msg.length + len) < max_message_length) 
        {
            m_Msg.length += len;
        } 
        else 
        {
            // no enough space and cut msg
            len = (max_message_length-1) - m_Msg.length;
            m_Msg.length = max_message_length;
        }
        return true;
    }
    // no space
    return false;
}



