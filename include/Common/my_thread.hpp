#pragma once

#include <thread>
#include <chrono>
#include <functional>

namespace myspace{
    class MyThread
    {
    public:
        MyThread() : m_bStarted(false){}
        virtual ~MyThread() { Stop(); }

        void Start()
        {
            if (m_bStarted)
            {
                return;
            }
            sp_thread.reset(new std::thread(std::bind(&MyThread::Run, this), this));
            m_bStarted = true;
            sp_thread->detach();
            return;
        }

        void Stop()
        {
            if (m_bStarted)
            {
                sp_thread.reset();
                m_bStarted = false;
            }
            return;
        }

        void Sleep (const unsigned int& ms) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }

    protected:
        virtual void Run(void) = 0;
        bool m_bStarted;

    private:
        std::shared_ptr<std::thread> sp_thread;
    };

}