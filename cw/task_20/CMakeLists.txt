project(cw_task_20)

add_executable(cw_task_20
               src/main.cpp
               src/model/Car.cpp src/model/Car.h
               src/common.cpp src/common.h
               src/TransAgency.cpp src/TransAgency.h
               src/scr/MainScript.cpp src/scr/MainScript.h
               src/scr/CarListScript.cpp src/scr/CarListScript.h)

target_include_directories(cw_task_20 PRIVATE src)
target_link_libraries(cw_task_20 wce_lib)

set_target_properties(cw_task_20 PROPERTIES
                      LINK_FLAGS ${WCE_LINK_FLAGS})