# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bossman/projects/AED/navigate/src_phase2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bossman/projects/AED/navigate/src_phase2/build

# Include any dependencies generated for this target.
include CMakeFiles/navigate.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/navigate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/navigate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/navigate.dir/flags.make

CMakeFiles/navigate.dir/navigate.c.o: CMakeFiles/navigate.dir/flags.make
CMakeFiles/navigate.dir/navigate.c.o: /home/bossman/projects/AED/navigate/src_phase2/navigate.c
CMakeFiles/navigate.dir/navigate.c.o: CMakeFiles/navigate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bossman/projects/AED/navigate/src_phase2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/navigate.dir/navigate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/navigate.dir/navigate.c.o -MF CMakeFiles/navigate.dir/navigate.c.o.d -o CMakeFiles/navigate.dir/navigate.c.o -c /home/bossman/projects/AED/navigate/src_phase2/navigate.c

CMakeFiles/navigate.dir/navigate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/navigate.dir/navigate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bossman/projects/AED/navigate/src_phase2/navigate.c > CMakeFiles/navigate.dir/navigate.c.i

CMakeFiles/navigate.dir/navigate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/navigate.dir/navigate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bossman/projects/AED/navigate/src_phase2/navigate.c -o CMakeFiles/navigate.dir/navigate.c.s

CMakeFiles/navigate.dir/graph.c.o: CMakeFiles/navigate.dir/flags.make
CMakeFiles/navigate.dir/graph.c.o: /home/bossman/projects/AED/navigate/src_phase2/graph.c
CMakeFiles/navigate.dir/graph.c.o: CMakeFiles/navigate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bossman/projects/AED/navigate/src_phase2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/navigate.dir/graph.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/navigate.dir/graph.c.o -MF CMakeFiles/navigate.dir/graph.c.o.d -o CMakeFiles/navigate.dir/graph.c.o -c /home/bossman/projects/AED/navigate/src_phase2/graph.c

CMakeFiles/navigate.dir/graph.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/navigate.dir/graph.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bossman/projects/AED/navigate/src_phase2/graph.c > CMakeFiles/navigate.dir/graph.c.i

CMakeFiles/navigate.dir/graph.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/navigate.dir/graph.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bossman/projects/AED/navigate/src_phase2/graph.c -o CMakeFiles/navigate.dir/graph.c.s

CMakeFiles/navigate.dir/stack.c.o: CMakeFiles/navigate.dir/flags.make
CMakeFiles/navigate.dir/stack.c.o: /home/bossman/projects/AED/navigate/src_phase2/stack.c
CMakeFiles/navigate.dir/stack.c.o: CMakeFiles/navigate.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/bossman/projects/AED/navigate/src_phase2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/navigate.dir/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/navigate.dir/stack.c.o -MF CMakeFiles/navigate.dir/stack.c.o.d -o CMakeFiles/navigate.dir/stack.c.o -c /home/bossman/projects/AED/navigate/src_phase2/stack.c

CMakeFiles/navigate.dir/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/navigate.dir/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bossman/projects/AED/navigate/src_phase2/stack.c > CMakeFiles/navigate.dir/stack.c.i

CMakeFiles/navigate.dir/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/navigate.dir/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bossman/projects/AED/navigate/src_phase2/stack.c -o CMakeFiles/navigate.dir/stack.c.s

# Object files for target navigate
navigate_OBJECTS = \
"CMakeFiles/navigate.dir/navigate.c.o" \
"CMakeFiles/navigate.dir/graph.c.o" \
"CMakeFiles/navigate.dir/stack.c.o"

# External object files for target navigate
navigate_EXTERNAL_OBJECTS =

navigate: CMakeFiles/navigate.dir/navigate.c.o
navigate: CMakeFiles/navigate.dir/graph.c.o
navigate: CMakeFiles/navigate.dir/stack.c.o
navigate: CMakeFiles/navigate.dir/build.make
navigate: CMakeFiles/navigate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/bossman/projects/AED/navigate/src_phase2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable navigate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/navigate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/navigate.dir/build: navigate
.PHONY : CMakeFiles/navigate.dir/build

CMakeFiles/navigate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/navigate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/navigate.dir/clean

CMakeFiles/navigate.dir/depend:
	cd /home/bossman/projects/AED/navigate/src_phase2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bossman/projects/AED/navigate/src_phase2 /home/bossman/projects/AED/navigate/src_phase2 /home/bossman/projects/AED/navigate/src_phase2/build /home/bossman/projects/AED/navigate/src_phase2/build /home/bossman/projects/AED/navigate/src_phase2/build/CMakeFiles/navigate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/navigate.dir/depend

