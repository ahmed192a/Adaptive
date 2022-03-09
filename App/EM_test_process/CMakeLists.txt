#################################### test process to test EM
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../processes)
add_executable(
    process1
    test_process.cpp 
)
target_compile_features(
    process1
    PRIVATE 
    cxx_std_17
)

target_link_libraries(
    process1
    PUBLIC
    ara_lib  
)
