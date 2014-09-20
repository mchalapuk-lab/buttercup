include_directories (${SRC_DIR}/include)
link_directories (${SRC_DIR}/src)
add_library (${PROJECT_NAME}
  run_suite.cpp
  failure_accumulator.cpp
  mutex_wait_notify.cpp
)

