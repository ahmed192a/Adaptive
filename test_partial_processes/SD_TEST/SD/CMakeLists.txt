add_executable(sd_process service_descovery.cpp)
target_compile_features(sd_process PRIVATE cxx_std_17)

target_link_libraries(sd_process PUBLIC ara_lib)
