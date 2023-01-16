set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../processes/SD)

add_executable(SD service_descovery.cpp)
target_compile_features(
    SD 
    PRIVATE 
    cxx_std_17)

target_link_libraries(
    SD 
    PUBLIC 
    ara_com_lib
    ara_exec_lib
)
