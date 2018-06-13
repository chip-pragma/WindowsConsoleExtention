project(Task20)

add_executable(${COURSE_TASK_20}
               src/main.cpp
               src/model/Car.cpp src/model/Car.h
               src/common.cpp src/common.h
               src/TransAgency.cpp src/TransAgency.h
               src/scr/MainScript.cpp src/scr/MainScript.h
               src/scr/CarListScript.cpp src/scr/CarListScript.h)

target_include_directories(${COURSE_TASK_20} PRIVATE src)
target_link_libraries(${COURSE_TASK_20} ${CPE_LIB_TARGET})
target_compile_features(${COURSE_TASK_20} PUBLIC cxx_std_17)

set_target_properties(${COURSE_TASK_20} PROPERTIES
                      OUTPUT_NAME "Task20_TransAgency"
                      LINK_FLAGS ${STATIC_STD_LINK})