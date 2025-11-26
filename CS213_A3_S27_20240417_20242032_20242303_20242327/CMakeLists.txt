cmake_minimum_required(VERSION 3.31)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR .)
include_directories(${SRC_DIR})

add_executable(Assignment_3
        ${SRC_DIR}/XO_Classes.cpp
        ${SRC_DIR}/XO_Demo.cpp
        ${SRC_DIR}/Numerical_Tic_Tac_Toe.cpp
        ${SRC_DIR}/SUS.cpp
        ${SRC_DIR}/FiveXO.cpp
        ${SRC_DIR}/FourXO.cpp
        ${SRC_DIR}/Obstacles.cpp
        ${SRC_DIR}/Misere_Tic_Tac_Teo.cpp
        ${SRC_DIR}/Four_in_a_row.cpp
        ${SRC_DIR}/Pyramid_Board.cpp
        ${SRC_DIR}/Infinity_Board.cpp


)