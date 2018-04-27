project(CPE_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(${EXECUTABLE_NAME}
               src/main.cpp src/processor/TestProcessor.cpp src/processor/TestProcessor.h src/script/TestScript.cpp src/script/TestScript.h src/common.cpp src/common.h)

target_include_directories(${EXECUTABLE_NAME} PRIVATE src)
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_CPE_NAME})

