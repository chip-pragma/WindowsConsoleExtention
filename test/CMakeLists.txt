project(CPE_Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(${EXECUTABLE_NAME}
        main.cpp)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_CPE_NAME})