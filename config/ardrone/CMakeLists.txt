cmake_minimum_required(VERSION 2.6.4)

FUNCTION(add_app)
    ADD_LIBRARY(${ARGN})
    SET_TARGET_PROPERTIES(${ARGV0} PROPERTIES PREFIX "" )
ENDFUNCTION()

set(PROJECT_SOURCE_DIR $ENV{CFS_MISSION})
enable_testing()
set(BUILDNAME "SoftSim")
project(ardrone)

set(SYSROOT "/srv/nfs")

add_subdirectory(../.. main)

# Set the PSP and OS
set(PSP "ardrone2")
set(OS "posix")

# Create the sysroot directory and copy the startup script.
file(MAKE_DIRECTORY ${SYSROOT}/cf/apps)
file(MAKE_DIRECTORY ${SYSROOT}/cf/download)
file(MAKE_DIRECTORY ${SYSROOT}/cf/log)
file(MAKE_DIRECTORY ${SYSROOT}/cf/upload)
file(MAKE_DIRECTORY ${SYSROOT}/ram)
configure_file(cfe_es_startup.scr ${SYSROOT}/cf/apps COPYONLY)

# Set the directory where all the build products are going to go.
set(INSTALL_DIR	${SYSROOT}/cf/apps)

# Include the global mission and build specific include directories.
include_directories(inc)
include_directories($ENV{CFS_MISSION_INC})

# Build the main CFE executable file.
add_subdirectory($ENV{CFE_CORE_SRC}/make cfe)

add_subdirectory(tools tools)

# Build each application, documentation, tables, and unit tests.
add_subdirectory(apps apps)
