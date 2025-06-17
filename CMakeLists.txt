cmake_minimum_required(VERSION 3.26)
project(probds-lite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(probds INTERFACE)
target_include_directories(probds INTERFACE include)

add_executable(test_bloom tests/test_bloom.cpp)
target_link_libraries(test_bloom PRIVATE probds)

enable_testing()
add_test(NAME bloom COMMAND test_bloom)
