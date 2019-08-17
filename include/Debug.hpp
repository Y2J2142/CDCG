#include <iosfwd>
#include <utility>
#include <string_view>
#include <cstdio>
namespace CDCG::Utility {

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
struct EXPORT Debug {

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

	enum class DebugLevel {
		STANDARD,
		ERROR
	};

    
	FILE* file;

    Debug(DebugLevel);
    Debug();
	Debug(std::nullptr_t) = delete;
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

