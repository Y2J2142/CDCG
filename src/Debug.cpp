#include "Debug.hpp"
#include <iostream>
#include <iomanip>
namespace CDCG::Utility {

    Debug::Debug(std::ostream& str) : stream{str} {}
    Debug::Debug() : stream{std::cout} {}

    Debug& Debug::operator<<(Debug::Color c) {
        switch(c) {

        }

        return *this;
    }
    Debug& Debug::operator<<(Debug::BackgroundColor c) {
        switch(c) {

        
        }

        return *this;
    }
    
    Debug& Debug::operator<<(std::string_view sv) {
        stream << sv;
        return *this;
    }
    
    Debug& Debug::operator<<(std::nullptr_t) {
        stream << " null pointer ";
        return *this;
    }

    Debug& Debug::operator<<(const char * ccs) {
        stream << ccs;
        return *this;
    } 

    Debug& Debug::operator<<(bool b) {
        stream << std::boolalpha <<' ' << b << ' ';
        return *this;
    }
    Debug& Debug::operator<<(int val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(long val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(long long val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(unsigned val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(unsigned long val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(unsigned long long val) {
        stream << ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(float val) {
        stream.precision(5);
        stream <<  ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(double val) {
        stream.precision(10);
        stream <<  ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(long double val) {
        stream.precision(15);
        stream <<  ' ' << val << ' ';
        return *this;
    }
    Debug& Debug::operator<<(void * val) {
        stream << ' ' << static_cast<char*>(val) << ' ';
        return *this;
    }

    Debug::~Debug() {
        stream << Color::RESET << '\n';
    }

}


