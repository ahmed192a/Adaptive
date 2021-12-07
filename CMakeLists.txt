cmake_minimum_required(VERSION 3.0.0)
project(Adaptive_Platform VERSION 0.1.0)

# This AUTOSAR Adaptive Platform requires C++14
set(CMAKE_CXX_STANDARD 14)
# Enable 'rdyamic' switch to export the executable's symbols for debugging
set(CMAKE_ENABLE_EXPORTS 1)

include(CTest)
option(build_tests "Build all the tests." ON)


add_executable(Adaptive_Platform main.cpp)

add_subdirectory(src/ara/exec)
add_subdirectory(src/ara/core)

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    src/ara/core
    src/ara/exec
    
    )
    
target_link_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    src/ara/core
    src/ara/exec
    
    )
target_link_libraries(
    ${PROJECT_NAME}
    core
    exec
    
    )


#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

if(build_tests)
    enable_testing()

endif()
