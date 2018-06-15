project(cw_task8)

add_executable(cw_task8
               src/AccountingPcSoft/main.cpp
               src/AccountingPcSoft/Item.cpp src/AccountingPcSoft/Item.h
               src/AccountingPcSoft/System.cpp src/AccountingPcSoft/System.h)

target_include_directories(cw_task8 PRIVATE src)
#target_link_libraries(cw_task8 ${CPE_LIB_TARGET}) // Not use
set_target_properties(cw_task8 PROPERTIES
                      OUTPUT_NAME AccountingPcSoft/cwTask8)