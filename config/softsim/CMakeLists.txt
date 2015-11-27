cmake_minimum_required(VERSION 2.8)

project(ARDroneCFS)
set(PROJECT_SOURCE_DIR $ENV{CFS_MISSION})
enable_testing()

# Set the PSP and OS
set(PSP "pc-linux")
set(OS "posix")

# Set the directory where all the build products are going to go.
set(INSTALL_DIR	${CMAKE_CURRENT_SOURCE_DIR}/sysroot/cf/apps)

# Set the path to the elf2cfetbl utility
set(ELF2CFETBL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/elf2cfetbl)

# Include the global mission and build specific include directories.
include_directories(inc)
include_directories($ENV{CFS_MISSION_INC})

# Build the main CFE executable file.
add_subdirectory(cfe cfe)

# Build the elf2cfetbl utility
add_subdirectory(elf2cfetbl elf2cfetbl)

# Build each application and associated table(s)
add_subdirectory(cf cf)
#add_subdirectory(CmdIn CmdIn)
add_subdirectory(cs cs)
add_subdirectory(ds ds)
add_subdirectory(fm fm)
add_subdirectory(hk hk)
add_subdirectory(hs hs)
add_subdirectory(lc lc)
add_subdirectory(md md)
#add_subdirectory(sbn sbn)
add_subdirectory(sc sc)
add_subdirectory(sch sch)
#add_subdirectory(TlmOut TlmOut)

# Add target to generate all documentation.
add_custom_target(docs
    COMMENT "Generating all documentation." VERBATIM
	COMMAND make cfe-docs
	COMMAND make cf-docs
	COMMAND make cs-docs
	COMMAND make ds-docs
	COMMAND make fm-docs
	COMMAND make hk-docs
	COMMAND make hs-docs
	COMMAND make lc-docs
	COMMAND make md-docs
	COMMAND make sc-docs
	COMMAND make sch-docs
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
)