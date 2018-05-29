project(Task8)

add_executable(${COURSE_TASK_8}
               src/AccountingPcSoft/main.cpp src/AccountingPcSoft/Item.cpp src/AccountingPcSoft/Item.h
               src/AccountingPcSoft/System.cpp src/AccountingPcSoft/System.h)

target_include_directories(${COURSE_TASK_8} PRIVATE src)
#target_link_libraries(${COURSE_TASK_8} ${CPE_LIB_TARGET})
#target_compile_features(${COURSE_TASK_8} PUBLIC cxx_std_17)
set_target_properties(${COURSE_TASK_8} PROPERTIES
                      OUTPUT_NAME "Task8_AccountingPcSoft")