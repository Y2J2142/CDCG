#include "SBOVector.hpp"
#include <iostream>
#include <string>



int main () {
    CDCG::Containers::SBOVector<int> ints{};
    CDCG::Containers::SBOVector<std::string> strings{};

    ints.reserve(20);
    

	for (int i = 0; i < 10; ++i) {
        ints.push_back(i);
	}
    
    for(auto && i : ints)
        std::cout << i << '\n';

    strings.emplace_back("test");
    strings.emplace_back("test1");
    strings.emplace_back("test2");
    strings.emplace_back("test3");
    strings.emplace_back("test4");
    strings.emplace_back("test5");
    strings.emplace_back("test6");
    strings.emplace_back("test7");


    auto movedStrings(std::move(strings));

    CDCG::Containers::SBOVector<std::string> moveAssigned{};

    moveAssigned.emplace_back("test");
    moveAssigned.emplace_back("test11");
    moveAssigned.emplace_back("test12");
    moveAssigned.emplace_back("test13");
    moveAssigned.emplace_back("test14");
    moveAssigned.emplace_back("test15");
    moveAssigned.emplace_back("test16");
    moveAssigned.emplace_back("test17");
    

    moveAssigned = std::move(movedStrings);

    for(auto&& s : moveAssigned)
        std::cout << s << '\n';


    return 0;






}