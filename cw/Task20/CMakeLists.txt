project(cw_task20)

add_executable(cw_task20
               src/main.cpp
               src/model/Car.cpp src/model/Car.h
               src/common.cpp src/common.h
               src/TransAgency.cpp src/TransAgency.h
               src/scr/MainScript.cpp src/scr/MainScript.h
               src/scr/CarListScript.cpp src/scr/CarListScript.h)

target_include_directories(cw_task20 PRIVATE src)
target_link_libraries(cw_task20 wce_lib)

set_target_properties(cw_task20 PROPERTIES
                      OUTPUT_NAME TransAgency/cwTask20
                      LINK_FLAGS ${STATIC_STD_LINK})