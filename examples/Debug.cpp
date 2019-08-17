#include "Debug.hpp"
#include <limits>
#include <string_view>

using namespace CDCG::Utility;

int main() {
    Debug{} << Debug::Color::BLACK     << "BLACK";
    Debug{} << Debug::Color::RED       << "RED";
    Debug{} << Debug::Color::GREEN     << "GREEN";
    Debug{} << Debug::Color::YELLOW    << "YELLOW";
    Debug{} << Debug::Color::BLUE      << "BLUE";
    Debug{} << Debug::Color::MAGENTA   << "MAGENTA";
    Debug{} << Debug::Color::CYAN      << "CYAN";
    Debug{} << Debug::Color::WHITE     << "WHITE";


    Debug{} << Debug::BackgroundColor::BLACK   << "    ";
    Debug{} << Debug::BackgroundColor::RED     << "    ";
    Debug{} << Debug::BackgroundColor::GREEN   << "    ";
    Debug{} << Debug::BackgroundColor::YELLOW  << "    ";
    Debug{} << Debug::BackgroundColor::BLUE    << "    ";
    Debug{} << Debug::BackgroundColor::MAGENTA << "    ";
    Debug{} << Debug::BackgroundColor::CYAN    << "    ";
    Debug{} << Debug::BackgroundColor::WHITE   << "    ";

    Debug{} << Debug::Color::RED << nullptr;

    Debug{} << "This is boolean :" << true;
    Debug{} << "This is int :" << 1;
    Debug{} << "This is float :" << 1.234567f;
    Debug{} << "This is double :" << 1.2345678916;
    Debug{} << "This is true in red :" << Debug::Color::RED << true;
	Debug{} << "This is a string_view in Yellow :" << Debug::Color::YELLOW << std::string_view("string view test");




}

