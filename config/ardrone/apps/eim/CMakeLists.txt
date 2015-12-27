# Set what we're going to call the application file.
set(APP_FILE EIM)

# Process build independent CMake file in application directory.
add_subdirectory($ENV{CFS_APP_SRC}/eim/fsw/for_build app)
