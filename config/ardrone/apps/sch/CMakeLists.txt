# Set what we're going to call the application file.
set(APP_FILE SCH)

# Set path to the tables source code directory.
set(TABLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tables)

# Set path to the unit test build specific input directory.
set(UNIT_TEST_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_test)
	
# Process build dependent CMake file in build directory.
add_subdirectory(src custom)

# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/sch/fsw/for_build app)
