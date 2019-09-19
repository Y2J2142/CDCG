#include "ScopedTimer.hpp"
#include "Debug.hpp"
#include <cstdint>

using CDCG::Utility::Debug;

template<typename T>
constexpr decltype(auto) castHelper = [](auto&& duration ) {
    return std::chrono::duration_cast<T>(duration );
};


namespace CDCG::Utility {

    ScopedTimer::ScopedTimer(std::string str, Duration dur)
        :   msg{std::move(str)},
            duration{dur} {
            if(!msg.empty())
                CDCG::Utility::Debug{} << "Starting : " << msg;
            start = std::chrono::high_resolution_clock::now();
    }

    ScopedTimer::~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        switch(duration) {
            case Duration::ns : 
                Debug{} << msg << " took" << castHelper<std::chrono::nanoseconds>(end - start);
                return;
            case Duration::ms : 
                Debug{} << msg << " took" << castHelper<std::chrono::milliseconds>(end - start);
                return;
            case Duration::us :
                Debug{} << msg << " took" << castHelper<std::chrono::microseconds>(end - start);
                return;
            case Duration::s : 
                Debug{} << msg << " took" << castHelper<std::chrono::seconds>(end - start);
                return;
            case Duration::m : 
                Debug{} << msg << " took" << castHelper<std::chrono::minutes>(end - start);
                return;
            case Duration::h : 
                Debug{} << msg << " took" << castHelper<std::chrono::hours>(end - start);
                return;

        } 
    }

}