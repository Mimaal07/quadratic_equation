cmake_minimum_required(VERSION 3.14)
project(QuadraticEquation)

set(CMAKE_CXX_STANDARD 17)

add_executable(quadratic src/main.cpp src/interpreters.cpp src/solver.cpp)

enable_testing()
find_package(GTest REQUIRED)
add_executable(quadratic_tests tests/test_quadratic.cpp src/interpreters.cpp src/solver.cpp)
target_link_libraries(quadratic_tests GTest::gtest GTest::gtest_main)
add_test(NAME QuadraticTests COMMAND quadratic_tests)