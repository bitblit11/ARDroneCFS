cmake_minimum_required(VERSION 2.8)

# Set what we're going to call the application file.
set(APP_FILE SCH)

# Set path to the tables source code directory.
set(TABLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../tables)
	
# Process build dependent CMake file in build directory.
add_subdirectory(../src custom)

# Process build independent CMake file in application directory.
add_subdirectory(../../../../apps/SCH/fsw/for_build app)
