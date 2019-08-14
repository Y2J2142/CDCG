#include <iosfwd>
#include <utility>
#include <string_view>

namespace CDCG::Utility {

// namespace Color {
//         static constexpr auto BLACK   = "\u001b[30m";
//         static constexpr auto RED     = "\u001b[31m";
//         static constexpr auto GREEN   = "\u001b[32m";
//         static constexpr auto YELLOW  = "\u001b[33m";
//         static constexpr auto BLUE    = "\u001b[34m";
//         static constexpr auto MAGENTA = "\u001b[35m";
//         static constexpr auto CYAN    = "\u001b[36m";
//         static constexpr auto WHITE   = "\u001b[37m";
//         static constexpr auto RESET   = "\u001b[0m";
//     }

// namespace BackgroundColor {
//     static constexpr auto BLACK   = "\u001b[40m";
//     static constexpr auto RED     = "\u001b[41m";
//     static constexpr auto GREEN   = "\u001b[42m";
//     static constexpr auto YELLOW  = "\u001b[43m";
//     static constexpr auto BLUE    = "\u001b[44m";
//     static constexpr auto MAGENTA = "\u001b[45m";
//     static constexpr auto CYAN    = "\u001b[46m";
//     static constexpr auto WHITE   = "\u001b[47m";
//     static constexpr auto RESET   = "\u001b[0m";

// }



struct Debug{



    enum class Color {
        BLACK  
        ,RED    
        ,GREEN  
        ,YELLOW 
        ,BLUE   
        ,MAGENTA
        ,CYAN   
        ,WHITE  
        ,RESET  

    };

    enum class BackgroundColor {
        BLACK  
        ,RED    
        ,GREEN  
        ,YELLOW 
        ,BLUE   
        ,MAGENTA
        ,CYAN   
        ,WHITE  
        ,RESET  
    };

    
    std::ostream& stream;

    Debug(std::ostream&);
    Debug();
    Debug(const Debug&) = delete;
    Debug(Debug&&) = default;
    Debug& operator=(const Debug&) = delete;
    Debug& operator=(Debug&&) = delete;

    Debug& operator<<(Color);
    Debug& operator<<(BackgroundColor);
    Debug& operator<<(std::string_view sv);
    Debug& operator<<(const char *);
    Debug& operator<<(std::nullptr_t);
    Debug& operator<<(bool);
    Debug& operator<<(int);
    Debug& operator<<(long);
    Debug& operator<<(long long);
    Debug& operator<<(unsigned);
    Debug& operator<<(unsigned long);
    Debug& operator<<(unsigned long long);
    Debug& operator<<(float);
    Debug& operator<<(double);
    Debug& operator<<(long double);
    Debug& operator<<(void *);
    




    ~Debug();





};






















}

