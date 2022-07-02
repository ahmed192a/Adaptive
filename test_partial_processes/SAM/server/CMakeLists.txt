add_executable(server_sd1 server.cpp )
target_compile_features(
    server_sd1
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    server_sd1
    PUBLIC 
    ara_lib
    )
