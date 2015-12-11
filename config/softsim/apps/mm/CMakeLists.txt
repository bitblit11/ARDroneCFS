# Set what we're going to call the application file.
set(APP_FILE MM)

# Set path to the unit test build specific input directory.
set(UNIT_TEST_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_test)

# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/mm/fsw/for_build app)
