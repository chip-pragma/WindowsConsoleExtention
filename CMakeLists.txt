cmake_minimum_required(VERSION 3.9)

#Имя исполняемого файла
set(EXECUTABLE_NAME CPE_Test)
#Имя библиотеки CPE
set(LIBRARY_CPE_NAME cpe)

include_directories(
        cpe
        test
)

add_subdirectory(cpe)
add_subdirectory(test)