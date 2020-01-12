cmake_minimum_required(VERSION 3.5)

project(CDCG VERSION 0.0.0)

include(GNUInstallDirs)

add_library(Utility SHARED src/Debug.cpp include/Debug.hpp src/ScopedTimer.cpp include/ScopedTimer.hpp) 

file(GLOB src "examples/*.cpp")
file(GLOB tests "tests/*.cpp")

set(CMAKE_CXX_STANDARD 20)
foreach(file_path ${src})
 string( REPLACE ".cpp" "" new_name ${file_path} )
 get_filename_component(filename ${new_name} NAME)
 add_executable( ${filename} ${file_path} )
 target_link_libraries( ${filename} Utility)
endforeach()

find_package(Catch2 REQUIRED)

enable_testing()
foreach(file_path ${tests})
    string( REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
    target_link_libraries( ${filename} Utility)
    target_link_libraries( ${filename} Catch2::Catch2)
    include(CTest)
    include(ParseAndAddCatchTests)
    ParseAndAddCatchTests(${filename})
endforeach()



set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/catch)


