cmake_minimum_required(VERSION 3.9)

#Имя исполняемого файла
set(EXECUTABLE_NAME CPE_Test)
#Имя библиотеки CPE
set(LIBRARY_CPE_NAME CpeLib)
#Директория бинарников сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

#Статическая линковка библиотек STD MinGW
#set(CMAKE_CXX_FLAGS
#        "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")


#Библиотека
add_subdirectory(CpeLib)
#Демо приложение
add_subdirectory(test)