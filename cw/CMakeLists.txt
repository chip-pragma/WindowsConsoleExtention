project(wce_cw)

file(GLOB CW_TASK_DIRS "task_*")

message(STATUS "===== TASKS ADDING =====")
foreach (task_dir_full_name ${CW_TASK_DIRS})
    add_subdirectory(${task_dir_full_name})
    string(LENGTH
           "${CMAKE_CURRENT_SOURCE_DIR}" project_path_length)
    string(SUBSTRING
           ${task_dir_full_name}
           ${project_path_length}
           8 # length of "tast_XX"; XX -- task number
           task_dir_short_name)

    message(STATUS "${task_dir_short_name} -- added")
endforeach (task_dir_full_name)
message(STATUS "========================")