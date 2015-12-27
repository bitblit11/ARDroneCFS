# Set what we're going to call the application file.
set(APP_FILE SC)

# Set path to the tables source code directory.
set(TABLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tables)

# Set path to the unit test build specific input directory.
set(UNIT_TEST_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_test)
	
# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/sc/fsw/for_build app)
