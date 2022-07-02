
add_executable(cleint_sd main.cpp )
target_compile_features(
    cleint_sd 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    cleint_sd 
    PUBLIC 
    ara_lib
    )
