cmake_minimum_required(VERSION 3.9)

#Имя исполняемого файла
set(EXECUTABLE_NAME CPE_Test)
#Имя библиотеки CPE
set(LIBRARY_CPE_NAME CpeLib)
#Директория бинарников сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

#Статическая линковка библиотек STD MinGW
set(CMAKE_C_FLAGS
        "${CMAKE_C_FLAGS} -static-libgcc")
set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
#set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS
#        "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
#set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
#        "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")

add_subdirectory(CpeLib)
add_subdirectory(test)