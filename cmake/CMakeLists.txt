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




# option(BOOST_DISABLE_TESTS "Do not build test targets, even if building standalone" OFF)
# set(BOOST_ENABLE_CMAKE ON)

# # fectch boost uuid lib only


# FetchContent_Declare(
#         boost
#         GIT_REPOSITORY https://github.com/boostorg/boost.git 
#         GIT_TAG boost-1.78.0
#         GIT_SHALLOW TRUE
#         GIT_PROGRESS TRUE)
# FetchContent_MakeAvailable(boost)

# FetchContent_Declare(
#         boost-varient
#         GIT_REPOSITORY https://github.com/boostorg/variant.git
#         GIT_TAG boost-1.78.0
#         GIT_SHALLOW TRUE
#         GIT_PROGRESS TRUE)
# FetchContent_MakeAvailable(boost-varient)

# FetchContent_Declare(
#         boost-varient2
#         GIT_REPOSITORY https://github.com/boostorg/variant2.git
#         GIT_TAG boost-1.78.0
#         GIT_SHALLOW TRUE
#         GIT_PROGRESS TRUE)
# FetchContent_MakeAvailable(boost-varient2)

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


