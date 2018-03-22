cmake_minimum_required(VERSION 3.9)
project(ConsolePresentExtention)

set(CMAKE_CXX_STANDARD 14)

add_library(ConsolePresentExtention
        cpe/Console.cpp
        cpe/Console.h
        cpe/Enums.h
        cpe/Menu.cpp
        cpe/Menu.h
        cpe/Table.cpp
        cpe/Table.h
        cpe/tools.cpp
        cpe/tools.h cpe/StringText.cpp cpe/StringText.h)