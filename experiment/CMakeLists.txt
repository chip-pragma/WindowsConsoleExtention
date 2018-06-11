project(CPE_Experiment)

add_executable(${CPE_EXPERIMENT_TARGET}
               src/main.cpp)

target_include_directories(${CPE_EXPERIMENT_TARGET} PRIVATE src)
target_compile_features(${CPE_EXPERIMENT_TARGET} PUBLIC cxx_std_17)

set_target_properties(${CPE_EXPERIMENT_TARGET} PROPERTIES
                      OUTPUT_NAME "CpeExperiment"
                      LINK_FLAGS ${STATIC_STD_LINK})
