cmake_minimum_required(VERSION 3.15)
project(Lab3MapDLLA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3MapDLLA
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h
        dynamicVector.h)
