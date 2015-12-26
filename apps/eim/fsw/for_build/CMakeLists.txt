# Set local variables
set(APPTARGET eim)

# Set source files
set(APP_SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/../src/app.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/cmds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/navcmds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/navdata.c)
	
# Set include paths
set(APP_INC_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/../src/)
include_directories(${APP_INC_DIRS})
include_directories(${CFE_INC_DIRS})
include_directories(${OSAL_INC_DIRS})
include_directories(${PSP_INC_DIRS})
	
# Build application
add_library(${APP_FILE} SHARED ${APP_SRC} ${APP_CUSTOM_SRC})

add_subdirectory(../unit_test unit_test)

# Generate documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/user_doxy @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/codewalk_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/codewalk_doxy @ONLY)
    add_custom_target(eim-docs
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/html/${APPTARGET}/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/latex/${APPTARGET}/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/html/${APPTARGET}/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/latex/${APPTARGET}/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/cwt/html/${APPTARGET}/
    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/cwt/latex/${APPTARGET}/
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/user_doxy
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/codewalk_doxy
        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/users_guide/latex/${APPTARGET}
        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/detailed_design/latex/${APPTARGET}
        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/cwt/latex/${APPTARGET}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
    )
endif(DOXYGEN_FOUND)