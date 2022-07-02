set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../processes/UCM_SERVER)

add_executable(UCM_SERVER ucm_server.cpp )
target_compile_features(
    UCM_SERVER 
    PRIVATE 
    cxx_std_17
    )

target_link_libraries(
    UCM_SERVER
    PUBLIC 
    ara_lib
    )
