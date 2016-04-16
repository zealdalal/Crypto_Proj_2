cmake_minimum_required(VERSION 3.5)
project(Crypto_Project_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Crypto_Project_2 ${SOURCE_FILES})