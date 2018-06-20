project(cw_task_08)

add_executable(cw_task_08
               src/main.cpp
               src/Item.cpp src/Item.h
               src/System.cpp src/System.h)

target_include_directories(cw_task_08 PRIVATE src)
#target_link_libraries(cw_task8 ${CPE_LIB_TARGET}) // Not use