# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.
# Set(FETCHCONTENT_QUIET FALSE)



# https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# set(source_ara_dir
#   "${CMAKE_SOURCE_DIR}/src/ara")
message(STATUS "Fetching JSON library")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.9.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(json)

option(BOOST_DISABLE_TESTS "Do not build test targets, even if building standalone" OFF)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.78.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(boost)



############################################################################################
# Get the CryptoPP CMakeLists.txt File for CryptoPP Package GIT_TAG Must be the Same
############################################################################################

message(CHECK_START "Fetching CryptoPP-CMAKE")
set(CRYPTOPP_CMAKE "cryptopp-cmake")
set(CRYPTOPP_GIT_TAG "CRYPTOPP_8_2_0")

FetchContent_Declare(
        ${CRYPTOPP_CMAKE}
        GIT_REPOSITORY  https://github.com/noloader/cryptopp-cmake
        GIT_TAG         ${CRYPTOPP_GIT_TAG}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(${CRYPTOPP_CMAKE})

if(NOT ${CRYPTOPP_CMAKE}_POPULATED)
    FetchContent_Populate(${CRYPTOPP_CMAKE})
endif()


############################################################################################
# Get the CryptoPP Package
############################################################################################

message(CHECK_START "Fetching CryptoPP")

set(CRYPTOPP "cryptopp")
FetchContent_Declare(
        ${CRYPTOPP}
        GIT_REPOSITORY  https://github.com/weidai11/cryptopp
        GIT
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(${CRYPTOPP})

if(NOT ${CRYPTOPP}_POPULATED)
    FetchContent_Populate(${CRYPTOPP})
    file(COPY ${${CRYPTOPP_CMAKE}_SOURCE_DIR}/CMakeLists.txt DESTINATION ${${CRYPTOPP}_SOURCE_DIR})
    add_subdirectory(${${CRYPTOPP}_SOURCE_DIR} ${${CRYPTOPP}_BINARY_DIR})
endif()
include_directories(${${CRYPTOPP}_SOURCE_DIR})

# Set Cryptopp library properties every time after the first population
if(${CRYPTOPP}_POPULATED)
    # Build shared or static library
    set(BUILD_SHARED_CRYPTOPP_OLD ${BUILD_SHARED})
    set(BUILD_SHARED ON CACHE INTERNAL "Build CryptoPP SHARED libraries")
    message("Build CryptoPP shared lib is set to: ${BUILD_SHARED}")
    if(${BUILD_SHARED} STREQUAL "ON")
        set(CRYPTOPP "cryptopp-shared")
        else ()
            set(CRYPTOPP "cryptopp-static")
    endif()
    set(BUILD_SHARED ${BUILD_SHARED_CRYPTOPP_OLD} CACHE BOOL "Type of libraries to build" FO
RCE)
endif()



file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/ara/*.cpp")



add_library(
  ara_lib
  ${SOURCE_LIST}
  ${HEADER_LIST}
)
target_include_directories(
  ara_lib 
  PUBLIC 
  ../include
)
target_link_libraries(
  ara_lib 
  PUBLIC 
  nlohmann_json::nlohmann_json
  crypto++
  # Boost::bind
  # Boost::asio
  Boost::uuid
  Boost::variant2
  ${CMAKE_THREAD_LIBS_INIT}
)

target_compile_features(
  ara_lib 
  PUBLIC 
  cxx_std_17
)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})


