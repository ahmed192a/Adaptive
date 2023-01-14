# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.




# https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html


# set(source_ara_dir
#   "${CMAKE_SOURCE_DIR}/src/ara")


file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")



add_library(
  ara_lib
  ${SOURCE_LIST}
  ${HEADER_LIST}
)
target_include_directories(
  ara_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)
target_link_libraries(
  ara_lib 
  PUBLIC 
  nlohmann_json::nlohmann_json
  # -lcryptopp
  # -lcrypto++
  # Boost::bind
  # Boost::asio
  # Boost::uuid
  # Boost::variant2
  pthread
  cryptopp::cryptopp
  stduuid
)

target_compile_features(
  ara_lib 
  PUBLIC 
  cxx_std_17
)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/src"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}) 

# copy headers to build directory with same structure
foreach(HEADER ${HEADER_LIST})
  file(RELATIVE_PATH RELATIVE_HEADER ${PROJECT_SOURCE_DIR}/src ${HEADER})
  get_filename_component(HEADER_PATH ${RELATIVE_HEADER} DIRECTORY)
  file(COPY ${HEADER} DESTINATION ${CMAKE_BINARY_DIR}/include/${HEADER_PATH})
endforeach()


# disable install for all dependencies 
set(CMAKE_INSTALL_DO_STRIP 1)
set(CMAKE_INSTALL_DO_STRIP_RUNTIME 1)
set(CMAKE_INSTALL_DO_STRIP_LIBRARY 1)
set(CMAKE_INSTALL_DO_STRIP_ARCHIVE 1)

# install the library
install(
  TARGETS ara_lib
  EXPORT ara_lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# install the headers
install(
  DIRECTORY ${CMAKE_BINARY_DIR}/include/ara/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
)
