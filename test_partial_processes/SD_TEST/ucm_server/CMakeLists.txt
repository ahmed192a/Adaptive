add_executable(ucm_server_test ucm_server.cpp )
target_compile_features(
    ucm_server_test 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    ucm_server_test 
    PUBLIC 
    ara_lib
    )
