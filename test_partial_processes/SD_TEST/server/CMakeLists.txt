add_executable(server_sd server.cpp )
target_compile_features(
    server_sd 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    server_sd 
    PUBLIC 
    ara_lib
    )
