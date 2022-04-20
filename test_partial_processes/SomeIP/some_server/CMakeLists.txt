
add_executable(server_someip server_someip.cpp )
target_compile_features(
    server_someip 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    server_someip 
    PUBLIC 
    ara_lib
    )
