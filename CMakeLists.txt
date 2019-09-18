cmake_minimum_required(VERSION 3.12)

project(CDCG VERSION 0.0.0)

include(GNUInstallDirs)


add_executable(Range examples/Range.cpp)
add_executable(Array examples/Array.cpp)
add_executable(BabyVector examples/BabyVector.cpp)
add_executable(LazyArray examples/LazyArray.cpp)



add_library(Utility SHARED src/Debug.cpp include/Debug.hpp) 

add_executable(Debug examples/Debug.cpp )
target_link_libraries(Debug Utility)


target_compile_features(Range PUBLIC cxx_std_17)
target_compile_options(Range PRIVATE )


target_compile_features(Array PUBLIC cxx_std_17)
target_compile_options(Array PRIVATE )



target_compile_features(BabyVector PUBLIC cxx_std_17)
target_compile_options(BabyVector PRIVATE )
target_link_libraries(BabyVector Utility)


target_compile_features(LazyArray PUBLIC cxx_std_17)
target_compile_options(LazyArray PRIVATE )
target_link_libraries(LazyArray Utility)

target_compile_features(Debug PUBLIC cxx_std_17)
target_compile_options(Debug PRIVATE )



target_compile_features(Utility PUBLIC cxx_std_17)
target_compile_options(Utility PRIVATE)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)



