#################################### Main APP
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY src)
add_executable(
    ${PROJECT_NAME} 
    exec_main.cpp 
)

target_compile_features(
    ${PROJECT_NAME}  
    PRIVATE 
    cxx_std_17
)

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
    ara_exec_lib
    ara_log_lib
)

add_subdirectory(EM_test_process)
add_subdirectory(SD)
add_subdirectory(SM)
add_subdirectory(UCM)
add_subdirectory(OTA)


