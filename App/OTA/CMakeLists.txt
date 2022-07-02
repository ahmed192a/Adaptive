
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../processes/ota_process)
add_executable(
    ota_process
    ota_main.cpp
)
target_compile_features(
    ota_process
    PRIVATE 
    cxx_std_17
)

target_link_libraries(
    ota_process
    PUBLIC
    ara_lib  
)
