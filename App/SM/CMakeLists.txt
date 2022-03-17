
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../processes)
add_executable(
    sm_process
    sm_main.cpp
)
target_compile_features(
    sm_process
    PRIVATE 
    cxx_std_17
)

target_link_libraries(
    sm_process
    PUBLIC
    ara_lib  
)
