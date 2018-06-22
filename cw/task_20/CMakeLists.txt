project(cw_task_20)

add_executable(cw_task_20
               src/main.cpp
               src/model/Transport.cpp src/model/Transport.h
               src/common.cpp src/common.h
               src/TransAgency.cpp src/TransAgency.h
               src/scr/MainScript.cpp src/scr/MainScript.h
               src/scr/TransportListScript.cpp src/scr/TransportListScript.h)

target_include_directories(cw_task_20 PRIVATE src)
target_link_libraries(cw_task_20 wce_lib)

set_target_properties(cw_task_20 PROPERTIES
                      LINK_FLAGS ${WCE_LINK_FLAGS})