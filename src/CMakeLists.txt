# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.


# https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html


set(source_ara_core_dir "${CMAKE_SOURCE_DIR}/src/ara/core")
set(source_ara_com_dir "${CMAKE_SOURCE_DIR}/src/ara/com")
set(source_ara_exec_dir "${CMAKE_SOURCE_DIR}/src/ara/exec")
set(source_ara_log_dir "${CMAKE_SOURCE_DIR}/src/ara/Log_trace")
set(source_ara_sm_dir "${CMAKE_SOURCE_DIR}/src/ara/sm")
set(source_ara_crypto_dir "${CMAKE_SOURCE_DIR}/src/ara/crypto")
set(source_ara_ucm_dir "${CMAKE_SOURCE_DIR}/src/ara/ucm")


file (GLOB_RECURSE source_ara_core_files "${source_ara_core_dir}/*.cpp" "${source_ara_core_dir}/*.h")
file (GLOB_RECURSE source_ara_com_files "${source_ara_com_dir}/*.cpp" "${source_ara_com_dir}/*.h")
file (GLOB_RECURSE source_ara_exec_files "${source_ara_exec_dir}/*.cpp" "${source_ara_exec_dir}/*.h")
file (GLOB_RECURSE source_ara_log_files "${source_ara_log_dir}/*.cpp" "${source_ara_log_dir}/*.h")
file (GLOB_RECURSE source_ara_sm_files "${source_ara_sm_dir}/*.cpp" "${source_ara_sm_dir}/*.h")
file (GLOB_RECURSE source_ara_crypto_files "${source_ara_crypto_dir}/*.cpp" "${source_ara_crypto_dir}/*.h")
file (GLOB_RECURSE source_ara_ucm_files "${source_ara_ucm_dir}/*.cpp" "${source_ara_ucm_dir}/*.h")

add_library(
  ara_core_lib
  ${source_ara_core_files}
)

add_library(
  ara_com_lib
  ${source_ara_com_files}
)

add_library(
  ara_exec_lib
  ${source_ara_exec_files}
)

add_library(
  ara_log_lib
  ${source_ara_log_files}
)

add_library(
  ara_sm_lib
  ${source_ara_sm_files}
)

add_library(
  ara_crypto_lib
  ${source_ara_crypto_files}
)

add_library(
  ara_ucm_lib
  ${source_ara_ucm_files}
)

target_include_directories(
  ara_core_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_com_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_exec_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_log_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_sm_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_crypto_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  ara_ucm_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(
  ara_exec_lib
  PUBLIC
  ara_core_lib
  nlohmann_json::nlohmann_json
  pthread
)

target_link_libraries(
  ara_crypto_lib
  PUBLIC
  ara_core_lib
  nlohmann_json::nlohmann_json
  cryptopp::cryptopp
  pthread
)

target_link_libraries(
  ara_com_lib
  PUBLIC
  nlohmann_json::nlohmann_json
  pthread
  stduuid
)

target_link_libraries(
  ara_sm_lib
  PUBLIC
  ara_exec_lib
  ara_com_lib
)

target_link_libraries(
  ara_ucm_lib
  PUBLIC
  ara_com_lib
  ara_crypto_lib
)


file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.h")
# file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")



# add_library(
#   ara_lib
#   ${SOURCE_LIST}
#   ${HEADER_LIST}
# )
# target_include_directories(
#   ara_lib 
#   PUBLIC 
#   "${PROJECT_SOURCE_DIR}/src"
# )
# target_link_libraries(
#   ara_lib 
#   PUBLIC 
#   nlohmann_json::nlohmann_json
#   # -lcryptopp
#   # -lcrypto++
#   # Boost::bind
#   # Boost::asio
#   # Boost::uuid
#   # Boost::variant2
#   pthread
#   cryptopp::cryptopp
#   stduuid
# )

# target_compile_features(
#   ara_lib 
#   PUBLIC 
#   cxx_std_17
# )


###########################################################################
set(source_ota_dir "${PROJECT_SOURCE_DIR}/src/OTA")
set(source_sdc_dir "${PROJECT_SOURCE_DIR}/src/SD_c")
set(source_sds_dir "${PROJECT_SOURCE_DIR}/src/SD_s")

file (GLOB_RECURSE source_ota_files "${source_ota_dir}/*.cpp" "${source_ota_dir}/*.h")
file (GLOB_RECURSE source_sdc_files "${source_sdc_dir}/*.cpp" "${source_sdc_dir}/*.h")
file (GLOB_RECURSE source_sds_files "${source_sds_dir}/*.cpp" "${source_sds_dir}/*.h")

add_library(
  ota_lib
  ${source_ota_files}
)

add_library(
  sdc_lib
  ${source_sdc_files}
)

add_library(
  sds_lib
  ${source_sds_files}
)

target_include_directories(
  ota_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  sdc_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(
  sds_lib 
  PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(
  sdc_lib
  PUBLIC
  ara_com_lib
)

target_link_libraries(
  sds_lib
  PUBLIC
  ara_com_lib
)

##########3




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





# # disable install for all dependencies 
# set(CMAKE_INSTALL_DO_STRIP 1)
# set(CMAKE_INSTALL_DO_STRIP_RUNTIME 1)
# set(CMAKE_INSTALL_DO_STRIP_LIBRARY 1)
# set(CMAKE_INSTALL_DO_STRIP_ARCHIVE 1)

# # install the library
# install(
#   TARGETS ara_lib
#   EXPORT ara_lib
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#   INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
# # install the headers
# install(
#   DIRECTORY ${CMAKE_BINARY_DIR}/include/ara/
#   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
# )
