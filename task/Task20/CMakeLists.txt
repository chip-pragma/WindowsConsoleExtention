project(Task20)

add_executable(${COURSE_TASK_20}
               src/TransAgency/main.cpp
               src/TransAgency/vm/MainVM.cpp src/TransAgency/vm/MainVM.h
               src/TransAgency/view/MainView.cpp src/TransAgency/view/MainView.h
               src/TransAgency/model/Car.cpp src/TransAgency/model/Car.h
               src/TransAgency/common.cpp src/TransAgency/common.h
               src/TransAgency/TransAgency.cpp src/TransAgency/TransAgency.h
               src/TransAgency/view/CarListView.cpp src/TransAgency/view/CarListView.h
               src/TransAgency/vm/CarListVM.cpp src/TransAgency/vm/CarListVM.h)

target_include_directories(${COURSE_TASK_20} PRIVATE src)
target_link_libraries(${COURSE_TASK_20} ${CPE_LIB_TARGET})
target_compile_features(${COURSE_TASK_20} PUBLIC cxx_std_17)

set_target_properties(${COURSE_TASK_20} PROPERTIES
                      OUTPUT_NAME "Task20_TransAgency"
                      LINK_FLAGS ${STATIC_STD_LINK})