cmake_minimum_required(VERSION 3.9)

#Имя исполняемого файла
set(CPE_TEST_TARGET CPE_Test)
#Имя библиотеки CPE
set(CPE_LIB_TARGET CpeLib)
#Курсовые
set(COURSE_TASK_20 Task20)
#Директория бинарников сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

#  ----------------------------------
# | Добавляем параметры компилятора |
# ----------------------------------
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
# GNU (GCC, MinGW)
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # Статическая линковка std-библиотек
    # Похоже, что плохо использовать -Wl,-allow-multiple-definition
    set(STATIC_STD_LINK "-static")

    # !!! Почему не работает???
    # target_compile_options(${CPE_LIB_TARGET} BEFORE PUBLIC ${STATIC_STD_LINK})

    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} ${STATIC_STD_LINK}")
    message(STATUS "Add compile options: ${STATIC_STD_LINK}")

else ()
    message(FATAL_ERROR "Unknown compiler! Please check and resolve it.")
endif ()

#Библиотека
add_subdirectory(CpeLib)
#Демо приложение
add_subdirectory(test)
#Курсовые
#add_subdirectory(Task20)