cmake_minimum_required(VERSION 3.9)

#Имя исполняемого файла
set(CPE_TEST_TARGET CPE_Test)
set(CPE_EXPERIMENT_TARGET CPE_Experiment)
#Имя библиотеки CPE
set(CPE_LIB_TARGET cpe)
#Курсовые
set(COURSE_TASK_8 Task8)
set(COURSE_TASK_20 Task20)
#Директория бинарников сборки
set(STATIC_LIB_OUTPUT_DIRECTORY "../builds/static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../builds/bin)
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
message(STATUS "Add compile options: ${STATIC_STD_LINK}")


#Библиотека
add_subdirectory(CpeLib)
#Демо приложение
add_subdirectory(test)
add_subdirectory(experiment)
##Курсовые
add_subdirectory(task/Task8)
add_subdirectory(task/Task20)