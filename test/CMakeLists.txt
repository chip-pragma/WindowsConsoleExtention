project(CPE_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(${EXECUTABLE_NAME}
        main.cpp processor/TestProcessor.cpp processor/TestProcessor.h script/TestScript.cpp script/TestScript.h common.cpp common.h)

include_directories(../CpeLib)

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_CPE_NAME})