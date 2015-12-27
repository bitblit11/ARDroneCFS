cmake_minimum_required(VERSION 2.6.4)

set(PROJECT_SOURCE_DIR $ENV{CFS_MISSION})
enable_testing()
set(BUILDNAME "SoftSim")
project(softsim)

add_subdirectory(../.. main)
#include(../../CMakeLists.txt)

# Set the PSP and OS
set(PSP "pc-linux")
set(OS "posix")

# Create the sysroot directory and copy the startup script.
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/apps)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/download)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/log)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/upload)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sysroot/ram)
configure_file(cfe_es_startup.scr ${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/apps COPYONLY)

# Set the directory where all the build products are going to go.
set(INSTALL_DIR	${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/apps)

# Include the global mission and build specific include directories.
include_directories(inc)
include_directories($ENV{CFS_MISSION_INC})

# Build the main CFE executable file.
add_subdirectory($ENV{CFE_CORE_SRC}/make cfe)

add_subdirectory(tools tools)

# Build each application, documentation, tables, and unit tests.
add_subdirectory(apps apps)
