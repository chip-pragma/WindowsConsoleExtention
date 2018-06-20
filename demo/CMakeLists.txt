project(wce_demo)

add_executable(wce_demo
               src/main.cpp src/main.h
               src/common.cpp src/common.h
               src/TestScript.cpp src/TestScript.h)

target_include_directories(wce_demo PRIVATE src)
target_link_libraries(wce_demo wce_lib)
set_target_properties(wce_demo PROPERTIES
                      OUTPUT_NAME "demoWCE"
                      LINK_FLAGS ${WCE_LINK_FLAGS})
