cmake_minimum_required(VERSION 3.20)

project(tensor-calculator)

set(CMAKE_CXX_STANDARD 17)

set(
  SOURCE_FILES
  src/main.cpp
  src/matrix/matrix.cpp
)

add_executable(tensor-calculator ${SOURCE_FILES})
