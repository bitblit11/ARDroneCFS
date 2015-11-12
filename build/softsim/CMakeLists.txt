cmake_minimum_required(VERSION 2.8)

include_directories(inc)
include_directories(../mission_inc)
include_directories(../../CFE/fsw/cfe-core/src/es)
include_directories(../../CFE/fsw/cfe-core/src/evs)
include_directories(../../CFE/fsw/cfe-core/src/fs)
include_directories(../../CFE/fsw/cfe-core/src/inc)
include_directories(../../CFE/fsw/cfe-core/src/sb)
include_directories(../../CFE/fsw/cfe-core/src/tbl)
include_directories(../../CFE/fsw/cfe-core/src/time)
include_directories(../../OSAL/src/os/inc)
include_directories(../../OSAL/src/os/posix)
include_directories(../../PSP/fsw/inc)
include_directories(../../PSP/fsw/pc-linux/inc)
include_directories(../../PSP/fsw/shared)


add_subdirectory(../../CFE/fsw/cfe-core/src cfe)
add_subdirectory(../../OSAL/src/os osal)
add_subdirectory(../../PSP/fsw/ psp)

add_executable(core-bin dummy.c)
SET_TARGET_PROPERTIES(core-bin PROPERTIES ENABLE_EXPORTS TRUE)
set_target_properties(core-bin PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(core-bin CFE_LIB OSAL_LIB PSP_LIB)