
add_executable(cleint_someip client_someip.cpp )
target_compile_features(
    cleint_someip 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    cleint_someip 
    PUBLIC 
    ara_lib
    )
