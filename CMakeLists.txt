cmake_minimum_required(VERSION 3.9)

#Стандарт C++
set(CMAKE_CXX_STANDARD 17)
# Статическая линковка std-библиотек
set(WCE_LINK_FLAGS " ")


message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # GNU (GCC, MinGW)
    set(WCE_LINK_FLAGS "-static")
else ()
    message(FATAL_ERROR "Unknown compiler! Please check and resolve it.")
endif ()
message(STATUS "Add compile options: WCE_LINK_FLAGS = ${WCE_LINK_FLAGS}")


#Библиотека
add_subdirectory(lib)
#Демо приложение
add_subdirectory(demo)
add_subdirectory(test)
##Курсовые
add_subdirectory(cw)