cmake_minimum_required(VERSION 3.29)
project(HW3_2425B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3_2425B
    main.cpp
    Person.cpp
    Person.h
    SortedList.h
    Task.cpp
    Task.h
    TaskManager.h
        TaskManager.cpp)
