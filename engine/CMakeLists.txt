project(sequel-engine LANGUAGES C CXX)

add_library(
  sequel 
  SHARED
  src/core.c
)

target_include_directories(sequel PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(SDL3 CONFIG REQUIRED)

target_link_libraries(
  sequel
  PRIVATE 
  SDL3::SDL3
)
