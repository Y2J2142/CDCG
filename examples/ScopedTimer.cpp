#include "ScopedTimer.hpp"
#include <thread>
#include <chrono>


using namespace CDCG::Utility;


int main() {
    ScopedTimer t{"test", Duration::us};
    std::this_thread::sleep_for(std::chrono::seconds(1));
}