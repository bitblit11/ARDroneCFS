# Add the mission and build specific includes
include_directories(../inc)
include_directories(../../mission_inc)

# Process the Elf2CfeTbl CMake file.
add_subdirectory(../../../CFE/tools/elf2cfetbl src)

# Include Elf2CfeTbl specific include directories.
include_directories(${ELF2CFETBL_INC})

# Create the executable file.
add_executable(elf2cfetbl ${ELF2CFETBL_SRC})
set_target_properties(elf2cfetbl PROPERTIES ENABLE_EXPORTS TRUE)
set_target_properties(elf2cfetbl PROPERTIES LINKER_LANGUAGE C)
set_target_properties(elf2cfetbl PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS} LINK_FLAGS ${LINK_FLAGS})
