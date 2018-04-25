project(CPE_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(${EXECUTABLE_NAME}
               main.cpp TestProcessor.cpp TestProcessor.h TestScript.cpp TestScript.h)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_CPE_NAME})