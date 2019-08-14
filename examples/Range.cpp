#include <Range.hpp>
#include <iostream>

using namespace CDCG::Ranges;
int main(){

    std::cout << "Number of elements in Range 1-11 with step = 2 : " << Range<int>{1,11,2}.size() << '\n';
    for(const auto& t : Range<int>{1, 11, 2})
        std::cout << t <<' ';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Number of elements in Range 0-21 : " << Range<int>{0,21}.size() << '\n';
    for(const auto& t : Range<int>{0, 21})
        std::cout << t << ' ';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Number of elements in Range 0f-1f : " << Range<float>{0.f,1.f,0.1f}.size() << '\n';
    for(const auto t : Range<float>{0.f, 1.f, 0.1f}) 
        std::cout << t << ' ';
    std::cout << '\n';
    std::cout << '\n';
    return 0;
}
