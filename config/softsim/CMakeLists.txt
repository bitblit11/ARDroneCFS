cmake_minimum_required(VERSION 2.8)

#Set the PSP and OS
set(PSP "pc-linux")
set(OS "posix")

#Set the directory where all the build products are going to go.
set(INSTALL_DIR	${CMAKE_CURRENT_SOURCE_DIR}/sysroot/cf/apps)

#Set the path to the elf2cfetbl utility
set(ELF2CFETBL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/elf2cfetbl)

#Include the global mission and build specific include directories.
include_directories(inc)
include_directories($ENV{CFS_MISSION_INC})

#Build the main CFE executable file.
add_subdirectory(cfe cfe)

#Build the elf2cfetbl utility
add_subdirectory(elf2cfetbl elf2cfetbl)

#Build each application and associated table(s)
add_subdirectory(sch sch)
