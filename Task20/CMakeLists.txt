project(Task20)

add_executable(${COURSE_TASK_20} src/TransAgency/main.cpp src/TransAgency/vm/MainVM.cpp src/TransAgency/vm/MainVM.h src/TransAgency/view/MainView.cpp src/TransAgency/view/MainView.h)

target_include_directories(${COURSE_TASK_20} PRIVATE src)
target_link_libraries(${COURSE_TASK_20} ${CPE_LIB_TARGET})
target_compile_features(${COURSE_TASK_20} PUBLIC cxx_std_17)
set_target_properties(${COURSE_TASK_20} PROPERTIES
                      OUTPUT_NAME "Task20_TransAgency")