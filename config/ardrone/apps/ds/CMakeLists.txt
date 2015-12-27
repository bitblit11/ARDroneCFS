# Set what we're going to call the application file.
set(APP_FILE DS)

# Set path to the tables source code directory.
set(TABLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tables)

# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/ds/fsw/for_build app)
