# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mbenson/git/ARDroneCFS/build/softsim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mbenson/git/ARDroneCFS/build/softsim/build

# Include any dependencies generated for this target.
include cfe/time/CMakeFiles/CFE_TIME_LIB.dir/depend.make

# Include the progress variables for this target.
include cfe/time/CMakeFiles/CFE_TIME_LIB.dir/progress.make

# Include the compile flags for this target's objects.
include cfe/time/CMakeFiles/CFE_TIME_LIB.dir/flags.make

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/flags.make
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o: /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_api.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mbenson/git/ARDroneCFS/build/softsim/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o   -c /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_api.c

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.i"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_api.c > CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.i

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.s"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_api.c -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.s

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.requires:
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.requires

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.provides: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.requires
	$(MAKE) -f cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build.make cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.provides.build
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.provides

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.provides.build: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/flags.make
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o: /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_task.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mbenson/git/ARDroneCFS/build/softsim/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o   -c /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_task.c

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.i"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_task.c > CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.i

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.s"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_task.c -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.s

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.requires:
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.requires

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.provides: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.requires
	$(MAKE) -f cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build.make cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.provides.build
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.provides

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.provides.build: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/flags.make
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o: /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_tone.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mbenson/git/ARDroneCFS/build/softsim/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o   -c /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_tone.c

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.i"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_tone.c > CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.i

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.s"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_tone.c -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.s

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.requires:
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.requires

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.provides: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.requires
	$(MAKE) -f cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build.make cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.provides.build
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.provides

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.provides.build: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/flags.make
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o: /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_utils.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mbenson/git/ARDroneCFS/build/softsim/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o   -c /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_utils.c

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.i"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_utils.c > CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.i

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.s"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time/cfe_time_utils.c -o CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.s

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.requires:
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.requires

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.provides: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.requires
	$(MAKE) -f cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build.make cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.provides.build
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.provides

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.provides.build: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o

# Object files for target CFE_TIME_LIB
CFE_TIME_LIB_OBJECTS = \
"CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o" \
"CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o" \
"CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o" \
"CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o"

# External object files for target CFE_TIME_LIB
CFE_TIME_LIB_EXTERNAL_OBJECTS =

cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o
cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o
cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o
cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o
cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build.make
cfe/time/libCFE_TIME_LIB.a: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libCFE_TIME_LIB.a"
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && $(CMAKE_COMMAND) -P CMakeFiles/CFE_TIME_LIB.dir/cmake_clean_target.cmake
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CFE_TIME_LIB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build: cfe/time/libCFE_TIME_LIB.a
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/build

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/requires: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_api.c.o.requires
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/requires: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_task.c.o.requires
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/requires: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_tone.c.o.requires
cfe/time/CMakeFiles/CFE_TIME_LIB.dir/requires: cfe/time/CMakeFiles/CFE_TIME_LIB.dir/cfe_time_utils.c.o.requires
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/requires

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/clean:
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time && $(CMAKE_COMMAND) -P CMakeFiles/CFE_TIME_LIB.dir/cmake_clean.cmake
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/clean

cfe/time/CMakeFiles/CFE_TIME_LIB.dir/depend:
	cd /home/mbenson/git/ARDroneCFS/build/softsim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mbenson/git/ARDroneCFS/build/softsim /home/mbenson/git/ARDroneCFS/CFE/fsw/cfe-core/src/time /home/mbenson/git/ARDroneCFS/build/softsim/build /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time /home/mbenson/git/ARDroneCFS/build/softsim/build/cfe/time/CMakeFiles/CFE_TIME_LIB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cfe/time/CMakeFiles/CFE_TIME_LIB.dir/depend

