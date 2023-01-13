# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.




# https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html


# set(source_ara_dir
#   "${CMAKE_SOURCE_DIR}/src/ara")


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
  # -lcryptopp
  # -lcrypto++
  # Boost::bind
  # Boost::asio
  Boost::uuid
  Boost::variant2
  pthread
  cryptopp::cryptopp
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


