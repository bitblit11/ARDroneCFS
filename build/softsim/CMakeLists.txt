cmake_minimum_required(VERSION 2.8)

#Set the directory where all the build products are going to go.
set(INSTALL_DIR	${CMAKE_CURRENT_BINARY_DIR}/sysroot/cf/apps)

SET(CMAKE_AR ${CMAKE_CURRENT_SOURCE_DIR}/elf2cfetbl/elf2cfetbl)
set(CMAKE_C_ARCHIVE_FINISH)
SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS> ${INSTALL_DIR}")
SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS> ${INSTALL_DIR}")

#Include the global mission and build specific include directories.
include_directories(inc)
include_directories(../mission_inc)

#Build the main CFE executable file.
add_subdirectory(cfe cfe)

#Build the elf2cfetbl utility
add_subdirectory(elf2cfetbl elf2cfetbl)

#Build each application and associated table(s)
add_subdirectory(sch/build sch)