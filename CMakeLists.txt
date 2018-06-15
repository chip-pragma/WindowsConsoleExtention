cmake_minimum_required(VERSION 3.9)

#Стандарт C++
set(CMAKE_CXX_STANDARD 17)
# Статическая линковка std-библиотек
set(STATIC_STD_LINK " ")


message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # GNU (GCC, MinGW)
    set(STATIC_STD_LINK "-static")
else ()
    message(FATAL_ERROR "Unknown compiler! Please check and resolve it.")
endif ()
message(STATUS "Add compile options: STATIC_STD_LINK = ${STATIC_STD_LINK}")


#Библиотека
add_subdirectory(lib)
#Демо приложение
add_subdirectory(demo)
add_subdirectory(test)
##Курсовые
add_subdirectory(cw/task8)
add_subdirectory(cw/task20)