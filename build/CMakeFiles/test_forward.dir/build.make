# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/mxh/homework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mxh/homework/build

# Include any dependencies generated for this target.
include CMakeFiles/test_forward.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_forward.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_forward.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_forward.dir/flags.make

CMakeFiles/test_forward.dir/test_template/test_forward.cc.o: CMakeFiles/test_forward.dir/flags.make
CMakeFiles/test_forward.dir/test_template/test_forward.cc.o: ../test_template/test_forward.cc
CMakeFiles/test_forward.dir/test_template/test_forward.cc.o: CMakeFiles/test_forward.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mxh/homework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_forward.dir/test_template/test_forward.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_forward.dir/test_template/test_forward.cc.o -MF CMakeFiles/test_forward.dir/test_template/test_forward.cc.o.d -o CMakeFiles/test_forward.dir/test_template/test_forward.cc.o -c /home/mxh/homework/test_template/test_forward.cc

CMakeFiles/test_forward.dir/test_template/test_forward.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_forward.dir/test_template/test_forward.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mxh/homework/test_template/test_forward.cc > CMakeFiles/test_forward.dir/test_template/test_forward.cc.i

CMakeFiles/test_forward.dir/test_template/test_forward.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_forward.dir/test_template/test_forward.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mxh/homework/test_template/test_forward.cc -o CMakeFiles/test_forward.dir/test_template/test_forward.cc.s

# Object files for target test_forward
test_forward_OBJECTS = \
"CMakeFiles/test_forward.dir/test_template/test_forward.cc.o"

# External object files for target test_forward
test_forward_EXTERNAL_OBJECTS =

test_forward: CMakeFiles/test_forward.dir/test_template/test_forward.cc.o
test_forward: CMakeFiles/test_forward.dir/build.make
test_forward: CMakeFiles/test_forward.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mxh/homework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_forward"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_forward.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_forward.dir/build: test_forward
.PHONY : CMakeFiles/test_forward.dir/build

CMakeFiles/test_forward.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_forward.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_forward.dir/clean

CMakeFiles/test_forward.dir/depend:
	cd /home/mxh/homework/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mxh/homework /home/mxh/homework /home/mxh/homework/build /home/mxh/homework/build /home/mxh/homework/build/CMakeFiles/test_forward.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_forward.dir/depend

