cmake_minimum_required(VERSION 3.31)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(Source)

add_executable(Assignment_3
        Source/BoardGame_Classes.h
        Source/XO_Classes.cpp
        Source/XO_Classes.h
        Source/XO_Demo.cpp
        Source/Numerical_Tic_Tac_Toe.cpp
        Source/Numerical_Tic_Tac_Toe.cpp
)
