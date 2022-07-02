add_executable(SD service_descovery.cpp)
target_compile_features(
    SD 
    PRIVATE 
    cxx_std_17)

target_link_libraries(
    SD 
    PUBLIC 
    ara_lib)
