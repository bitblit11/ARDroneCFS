cmake_minimum_required(VERSION 2.8)

# Set what we're going to call the application file.
set(APP_FILE CFSLIB)

# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/cfs_lib/fsw/for_build app)
