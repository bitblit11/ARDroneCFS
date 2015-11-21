# Set the PSP and OSAL for this build

# Set what we're going to call the executable file.
set(CFE_EXEC_FILE core-bin)

# Process the CFE CMake file.  This contains pretty much everything.
add_subdirectory($ENV{CFE_CORE_SRC}/make cfe)

# Set where to put the file.
set_target_properties(${CFE_EXEC_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR})

# Where to put applications
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR} PARENT_SCOPE)

# Where to put tables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${INSTALL_DIR} PARENT_SCOPE)

# Generate documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file($ENV{CFE_DIR}/docs/detail_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy @ONLY)
    configure_file($ENV{CFE_DIR}/docs/user_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/user_doxy @ONLY)
    add_custom_target(docs
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/html/cfe/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/latex/cfe/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/html/cfe/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/latex/cfe/
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/user_doxy
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

# Pass some variables up to the parent.
set(COMPILE_FLAGS ${COMPILE_FLAGS} PARENT_SCOPE)
set(LINK_FLAGS ${LINK_FLAGS} PARENT_SCOPE)
set(CFE_INC_DIRS ${CFE_INC_DIRS} PARENT_SCOPE)
set(OSAL_INC_DIRS ${OSAL_INC_DIRS} PARENT_SCOPE)
set(PSP_INC_DIRS ${PSP_INC_DIRS} PARENT_SCOPE)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} PARENT_SCOPE)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE)
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} PARENT_SCOPE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
SET(CMAKE_AR ${CMAKE_AR} PARENT_SCOPE)
set(CMAKE_C_ARCHIVE_FINISH ${CMAKE_C_ARCHIVE_FINISH} PARENT_SCOPE)
SET(CMAKE_CXX_ARCHIVE_CREATE ${CMAKE_CXX_ARCHIVE_CREATE} PARENT_SCOPE)
SET(CMAKE_C_ARCHIVE_CREATE ${CMAKE_C_ARCHIVE_CREATE} PARENT_SCOPE)
