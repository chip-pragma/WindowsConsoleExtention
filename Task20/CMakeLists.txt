project(Task20)

set(CMAKE_CXX_STANDARD 17)

add_executable(${COURSE_TASK_20} src/main.cpp)

target_include_directories(${COURSE_TASK_20} PRIVATE src)
target_link_libraries(${COURSE_TASK_20} ${CPE_LIB_TARGET})

set_target_properties(${COURSE_TASK_20} PROPERTIES
        OUTPUT_NAME "Task20_TransAgency")