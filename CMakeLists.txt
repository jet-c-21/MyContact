cmake_minimum_required(VERSION 3.15)
project(MyContact)

set(CMAKE_CXX_STANDARD 14)

file(GLOB MyContactSrc
        "src/*.hpp"
        "src/*.cpp")

add_executable(app main.cpp ${MyContactSrc})
#add_executable(test_1 test_1.cpp)