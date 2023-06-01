cmake_minimum_required(VERSION 3.21)
project(HW03)

set(CMAKE_CXX_STANDARD 98)

add_executable(HW03 main.cpp Metropolis.cpp Metropolis.h Junction.cpp Junction.h Road.cpp Road.h Car.cpp Car.h CarLinkedList.cpp CarLinkedList.h Simulator.cpp Simulator.h)
