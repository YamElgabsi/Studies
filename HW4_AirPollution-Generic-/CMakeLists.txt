cmake_minimum_required(VERSION 3.21)
project(HW04)

set(CMAKE_CXX_STANDARD 98)

add_executable(HW04 main.cpp Map.h LinkedList.h LinkedList_imp.h Map_imp.h Junction.cpp Junction.h Car.h Car.cpp Road.cpp Road.h Metropolis.cpp Metropolis.h Simulator.h Simulator.cpp Cars.cpp Cars.h)
