add_executable(classic_test classic.cpp )
target_compile_features(
    classic_test 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    classic_test 
    PUBLIC 
    ara_lib
    )
