project(sequel-sandbox LANGUAGES C CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
  main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE sequel)
