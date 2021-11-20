cmake_minimum_required(VERSION 3.5)

project(CDCG VERSION 0.0.0)

include(GNUInstallDirs)

file(GLOB src "examples/*.cpp")
file(GLOB tests "tests/*.cpp")

set(CMAKE_CXX_STANDARD 20)
foreach(file_path ${src})
 string( REPLACE ".cpp" "" new_name ${file_path} )
 get_filename_component(filename ${new_name} NAME)
 add_executable( ${filename} ${file_path} )
endforeach()

find_package(Catch2 3 REQUIRED)

enable_testing()
foreach(file_path ${tests})
    string( REPLACE ".cpp" "" new_name ${file_path} )
    get_filename_component(filename ${new_name} NAME)
    add_executable( ${filename} ${file_path} )
    target_link_libraries( ${filename} PRIVATE Catch2::Catch2WithMain)
    include(CTest)
    include(Catch)
    catch_discover_tests(${filename})
endforeach()



set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/catch)