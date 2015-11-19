cmake_minimum_required(VERSION 2.8)

SET(PSP "pc-linux")
SET(OSAL "posix")
SET(CMAKE_AR "../elf2cfetbl/elf2cfetbl")
set(CMAKE_C_ARCHIVE_FINISH)
SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS>")
SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> <OBJECTS>")


include_directories(inc)
include_directories(../mission_inc)
include_directories(../../apps/SCH/fsw/src)

add_subdirectory(../../CFE/fsw/cfe-core/src/make cfe)
add_subdirectory(../../OSAL/src/os/${OSAL} osal)
add_subdirectory(../../PSP/fsw/${PSP}/make psp)

include_directories(${CFE_INC_DIRS})
include_directories(${OSAL_INC_DIRS})
include_directories(${PSP_INC_DIRS})

add_executable(core-bin ${CFE_SRC} ${OSAL_SRC} ${PSP_SRC})
SET_TARGET_PROPERTIES(core-bin PROPERTIES ENABLE_EXPORTS TRUE)
set_target_properties(core-bin PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(core-bin pthread dl rt)
set_target_properties(core-bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../sysroot/cf/apps)
set_target_properties(core-bin PROPERTIES COMPILE_FLAGS "-m32 -g" LINK_FLAGS "-m32")


add_subdirectory(../../apps/SCH/fsw/for_build sch)
add_library(SCH SHARED ${SCH_SRC})
set_target_properties(SCH PROPERTIES LINKER_LANGUAGE C)
set_target_properties(SCH PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../sysroot/cf/apps)
set_target_properties(SCH PROPERTIES COMPILE_FLAGS "-m32 -g" LINK_FLAGS "-m32")


add_library(sch_def_msgtbl STATIC ${SCH_TABLES_A})
set_target_properties(sch_def_msgtbl PROPERTIES LINKER_LANGUAGE C)
set_target_properties(sch_def_msgtbl PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../sysroot/cf/apps)
set_target_properties(sch_def_msgtbl PROPERTIES COMPILE_FLAGS "-m32 -g" LINK_FLAGS "-m32")
SET_TARGET_PROPERTIES(sch_def_msgtbl PROPERTIES PREFIX "" SUFFIX ".tbl")

add_library(sch_def_schtbl STATIC ${SCH_TABLES_B})
set_target_properties(sch_def_schtbl PROPERTIES LINKER_LANGUAGE C)
set_target_properties(sch_def_schtbl PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../sysroot/cf/apps)
set_target_properties(sch_def_schtbl PROPERTIES COMPILE_FLAGS "-m32 -g" LINK_FLAGS "-m32")
SET_TARGET_PROPERTIES(sch_def_schtbl PROPERTIES PREFIX "" SUFFIX ".tbl")
