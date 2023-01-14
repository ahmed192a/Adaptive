Set(FETCHCONTENT_QUIET FALSE)


############################################################################################
# Install json lib  
############################################################################################

message(STATUS "Fetching JSON library")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.9.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(json)



############################################################################################
# Install uuid lib
############################################################################################

message(STATUS "Fetching UUID library")
FetchContent_Declare(
        uuid
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
        GIT_TAG  v1.2.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
# disable tests and benchmarks
set(UUID_BUILD_TESTS OFF CACHE INTERNAL "")
set(UUID_BUILD_BENCHMARKS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(uuid)

############################################################################################
# Get the CryptoPP CMakeLists.txt File for CryptoPP Package GIT_TAG Must be the Same
############################################################################################

message(CHECK_START "Fetching CryptoPP-CMAKE")
set(CRYPTOPP_CMAKE "cryptopp-cmake")
set(CRYPTOPP_GIT_TAG "CRYPTOPP_8_7_0_1")

FetchContent_Declare(
        ${CRYPTOPP_CMAKE}
        GIT_REPOSITORY  https://github.com/abdes/cryptopp-cmake.git
        GIT_TAG         ${CRYPTOPP_GIT_TAG}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${CRYPTOPP_CMAKE})


