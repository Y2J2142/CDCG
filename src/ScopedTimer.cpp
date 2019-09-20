#include "ScopedTimer.hpp"
#include "Debug.hpp"
#include <cstdint>



template<typename T>
constexpr decltype(auto) castHelper = [](auto&& duration ) {
    return std::chrono::duration_cast<T>(duration );
};


namespace CDCG::Utility {

    ScopedTimerBase::ScopedTimerBase(std::string&& str)
        :   msg{std::move(str)}  { 
                Debug{} << "Starting : " << msg;
                start = std::chrono::high_resolution_clock::now();
            }


    template<typename Resolution>
    ScopedTimer<Resolution>::ScopedTimer(std::string str)
        :   ScopedTimerBase{std::move(str)} {}

    template<typename Resolution>
    ScopedTimer<Resolution>::~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        Debug{} << msg << " took" << castHelper<Resolution>(end - start);
    }

    template struct ScopedTimer<std::chrono::nanoseconds>;
    template struct ScopedTimer<std::chrono::milliseconds>;
    template struct ScopedTimer<std::chrono::microseconds>;
    template struct ScopedTimer<std::chrono::seconds>;
    template struct ScopedTimer<std::chrono::minutes>;
    template struct ScopedTimer<std::chrono::hours>;

 
}