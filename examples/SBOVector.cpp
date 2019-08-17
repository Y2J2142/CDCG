#include "SBOVector.hpp"
#include <iostream>

//Non trivialy copyable type to test behaviour for both cases handled in the SBOVector
struct B {
	int t = 10;
	B() = default;
	B(B const&) { t++; }
};




int main () {
    CDCG::Containers::SBOVector<int> v{};
    CDCG::Containers::SBOVector<B> a{};

    v.reserve(20);
    

    for(int i = 0; i < 10; ++i) {
        v.push_back(i);
        a.push_back(B{});
    }
    
    for(auto && i : v)
        std::cout << i << '\n';


    return 0;






}