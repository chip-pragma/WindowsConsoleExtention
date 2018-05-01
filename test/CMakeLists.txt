project(CPE_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CPE_TEST_TARGET}
               src/main.cpp src/common.cpp src/common.h src/view/MainView.cpp src/view/MainView.h src/controller/MainController.cpp src/controller/MainController.h)

target_include_directories(${CPE_TEST_TARGET} PRIVATE src)
target_link_libraries(${CPE_TEST_TARGET} ${CPE_LIB_TARGET})

get_target_property(LIB_VER ${CPE_LIB_TARGET} VERSION)
set_target_properties(${CPE_TEST_TARGET} PROPERTIES
                      OUTPUT_NAME "CpeTest"
                      VERSION ${LIB_VER})
