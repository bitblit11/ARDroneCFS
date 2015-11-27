# Set the path to the elf2cfetbl utility
# Add the mission and build specific includes
include_directories(../../inc)
include_directories(../../../mission_inc)

# Process the Elf2CfeTbl CMake file.
add_subdirectory(../../../../CFE/tools/elf2cfetbl src)

# Include Elf2CfeTbl specific include directories.
include_directories(${ELF2CFETBL_INC})

# Create the executable file.
add_executable(elf2cfetbl ${ELF2CFETBL_SRC})
set_target_properties(elf2cfetbl PROPERTIES ENABLE_EXPORTS TRUE)
set_target_properties(elf2cfetbl PROPERTIES LINKER_LANGUAGE C)
set_target_properties(elf2cfetbl PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS} LINK_FLAGS ${LINK_FLAGS})
set(ELF2CFETBL_PATH ${CMAKE_CURRENT_BINARY_DIR}/elf2cfetbl)

# Set the elf2cfetbl utility as the archiver for tables
set(CMAKE_AR ${ELF2CFETBL_PATH} PARENT_SCOPE)
set(CMAKE_C_ARCHIVE_FINISH PARENT_SCOPE)
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS> ${INSTALL_DIR}" PARENT_SCOPE)
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS> ${INSTALL_DIR}" PARENT_SCOPE)
set(ELF2CFETBL_PATH ${ELF2CFETBL_PATH} PARENT_SCOPE)