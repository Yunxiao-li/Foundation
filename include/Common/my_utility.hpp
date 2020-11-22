#pragma once
#include <sstream>

namespace myspace{
    // Thread safe singleton
    template <typename T>
    class Singleton 
    {
    public:
        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        
    protected:
        Singleton() {}
        ~Singleton() {}
    };
}