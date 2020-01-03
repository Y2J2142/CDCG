cmake_minimum_required(VERSION 3.5)

project(CDCG VERSION 0.0.0)

include(GNUInstallDirs)

add_library(Utility SHARED src/Debug.cpp include/Debug.hpp src/ScopedTimer.cpp include/ScopedTimer.hpp) 

file(GLOB src "examples/*.cpp")
file(GLOB tests "tests/*.cpp")


foreach(file_path ${src})
 string( REPLACE ".cpp" "" new_name ${file_path} )
 get_filename_component(filename ${new_name} NAME)
 add_executable( ${filename} ${file_path} )
 target_link_libraries( ${filename} Utility)
endforeach()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "catch/cath.hpp")

enable_testing()
foreach(file_path ${tests})
    string( REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
    target_link_libraries( ${filename} Utility)
    target_link_libraries( ${filename} Catch)
    add_test(test ${filename})
endforeach()



set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/catch)


