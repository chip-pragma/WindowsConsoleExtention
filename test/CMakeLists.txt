project(CPE_Test)

add_executable(${CPE_TEST_TARGET}
               src/main.cpp src/common.cpp src/common.h src/main.h src/TestScript.cpp src/TestScript.h)

target_include_directories(${CPE_TEST_TARGET} PRIVATE src)
target_link_libraries(${CPE_TEST_TARGET} ${CPE_LIB_TARGET})
target_compile_features(${CPE_TEST_TARGET} PUBLIC cxx_std_17)

set_target_properties(${CPE_TEST_TARGET} PROPERTIES
                      OUTPUT_NAME "CpeTest"
                      LINK_FLAGS ${STATIC_STD_LINK})
