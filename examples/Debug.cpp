#include "Debug.hpp"
#include <limits>


using namespace CDCG::Utility;

int main() {
    Debug{} << Color::BLACK     << "BLACK";
    Debug{} << Color::RED       << "RED";
    Debug{} << Color::GREEN     << "GREEN";
    Debug{} << Color::YELLOW    << "YELLOW";
    Debug{} << Color::BLUE      << "BLUE";
    Debug{} << Color::MAGENTA   << "MAGENTA";
    Debug{} << Color::CYAN      << "CYAN";
    Debug{} << Color::WHITE     << "WHITE";


    Debug{} << BackgroundColor::BLACK   << "    ";
    Debug{} << BackgroundColor::RED     << "    ";
    Debug{} << BackgroundColor::GREEN   << "    ";
    Debug{} << BackgroundColor::YELLOW  << "    ";
    Debug{} << BackgroundColor::BLUE    << "    ";
    Debug{} << BackgroundColor::MAGENTA << "    ";
    Debug{} << BackgroundColor::CYAN    << "    ";
    Debug{} << BackgroundColor::WHITE   << "    ";

    Debug{} << Color::RED << nullptr;

    Debug{} << "This is boolean :" << true;
    Debug{} << "This is int :" << 1;
    Debug{} << "This is float :" << 1.234567f;
    Debug{} << "This is double :" << 1.2345678916;
    Debug{} << "This is true in red :" << Color::RED << true;




}

