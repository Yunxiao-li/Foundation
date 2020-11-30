#include <iostream>
#include <fstream>
#include <sstream>

#include "my_log.h"
#include "my_log_task.h"
#include "my_log_queue.h"

using namespace myspace;
using namespace myspace::Log;

std::map<std::string, std::ofstream*> LogTaskImpl::s_vFiles;
static bool my_log_started = true;
static bool my_log_finalized = false;


void LogTaskImpl::WriteMsg(const MsgInfo &msg) const 
{
    std::map<std::string, std::ofstream*>::iterator iter = s_vFiles.find(msg.file);
    if(WRITE_FILE_MODE_APP == msg.mode)
    {
        if(s_vFiles.end() == iter) 
        {
            std::ofstream *pFile = new std::ofstream(msg.path, std::ios::app);
            s_vFiles.insert(std::pair<std::string, std::ofstream *>(msg.path, pFile));
            iter = s_vFiles.find(msg.path);
        }
        if((NULL != iter->second) && (iter->second->is_open())) 
        {
            Write2file(*(iter->second), msg);
        }
    } 
    else if(WRITE_FILE_MODE_END == msg.mode) 
    {
        if(s_vFiles.end() != iter) 
        {
            if ((NULL != iter->second) && (iter->second->is_open())) 
            {
                iter->second->close();
                delete iter->second;
            }
            s_vFiles.erase(iter);
        }
    } 
    else if(WRITE_FILE_MODE_TURNC == msg.mode) 
    {
        if(s_vFiles.end() == iter) 
        {
            std::ofstream *pFile = new std::ofstream(msg.path, std::ios::out | std::ios::trunc);
            s_vFiles.insert(std::pair<std::string, std::ofstream *>(msg.path, pFile));
            iter = s_vFiles.find(msg.path);
        }
        if((0 != msg.length) && (NULL != iter->second) && (iter->second->is_open())) 
        {
            Write2file(*(iter->second), msg);
        }
    }
}

void LogTaskImpl::Write2file(std::ofstream& of, const MsgInfo& msg) const
{
    of << msg.level << " " << msg.time << " " << msg.source << " pid: " << msg.pid 
        << " " << msg.func << ": " << msg.line << " " << msg.message << std::endl;
}

bool LogTaskImpl::ReadQueue() 
{
    myspace::Log::MsgInfo message;
    if(myspace::Log::LogQueue::pop(message)) 
    {
        WriteMsg(message);
        return true;
    }
    return false;
}


void myspace::MyLog_Shutdown() 
{
    my_log_started = false;
    while(!my_log_finalized) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for_logging));
    }
}

void LogTaskImpl::Run(void) 
{
    s_vFiles.clear();
    // keep thread running untill shutdown
    while(my_log_started) 
    {
        if(!ReadQueue())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for_logging));
        }
    }
    // it can be shutdown when message queue is empty
    while(true) 
    {
        if(!ReadQueue())
            break;
    }
    my_log_finalized = true;
}


void LogTask::Start(void) 
{
    m_Impl.Start();
}

LogTask::~LogTask() 
{
    m_Impl.Stop();
}

void LogTask::Stop(void) 
{
    m_Impl.Stop();
}
