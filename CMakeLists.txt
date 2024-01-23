cmake_minimum_required(VERSION 3.26)
project(GrahamScan)

set(CMAKE_CXX_STANDARD 17)

add_executable(GrahamScan main.cpp
        graham_scan.hpp
        )
