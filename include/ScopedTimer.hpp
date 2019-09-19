#pragma once

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <string>
#include <ratio>
#include<chrono>


namespace CDCG::Utility {

    enum class Duration {ns, ms, us, s, m, h };

    struct EXPORT ScopedTimer {

        
        
        const std::string msg;
        Duration duration;
        std::chrono::system_clock::time_point start;

        ScopedTimer(std::string = "", Duration dur = Duration::ms);
        ~ScopedTimer();

    };

}
