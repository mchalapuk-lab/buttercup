include_directories (${SRC_DIR}/include)
link_directories (${SRC_DIR}/test ${SRC_DIR}/src)
add_executable (${PROJECT_NAME}-tests
  tests.cpp
  run_suite.cpp
)
target_link_libraries (${PROJECT_NAME}-tests ${PROJECT_NAME} gmock pthread)

