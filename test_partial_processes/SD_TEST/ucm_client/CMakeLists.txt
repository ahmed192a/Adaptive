add_executable(ucm_client_test ucm_client.cpp )
target_compile_features(
    ucm_client_test 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    ucm_client_test 
    PUBLIC 
    ara_lib
    )
