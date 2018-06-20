project(wce_test)

add_executable(wce_test
               src/main.cpp)

target_include_directories(wce_test PRIVATE src)
set_target_properties(wce_test PROPERTIES
                      OUTPUT_NAME testWCE
                      LINK_FLAGS ${WCE_LINK_FLAGS})
