cmake_minimum_required(VERSION 3.20)

project(tensor-calculator)

set(CMAKE_CXX_STANDARD 17)

set(MATRIX_CPP src/matrix/matrix.cpp)

add_executable(tensor-calculator src/main.cpp ${MATRIX_CPP})
add_executable(systems_of_linear_equations examples/systems_of_linear_equations.cpp ${MATRIX_CPP})
