# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wanglei/Desktop/hello-world/6.mpi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug

# Include any dependencies generated for this target.
include exam2021/CMakeFiles/2021-exam4.dir/depend.make

# Include the progress variables for this target.
include exam2021/CMakeFiles/2021-exam4.dir/progress.make

# Include the compile flags for this target's objects.
include exam2021/CMakeFiles/2021-exam4.dir/flags.make

exam2021/CMakeFiles/2021-exam4.dir/exam4.c.o: exam2021/CMakeFiles/2021-exam4.dir/flags.make
exam2021/CMakeFiles/2021-exam4.dir/exam4.c.o: ../exam2021/exam4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object exam2021/CMakeFiles/2021-exam4.dir/exam4.c.o"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/2021-exam4.dir/exam4.c.o -c /Users/wanglei/Desktop/hello-world/6.mpi/exam2021/exam4.c

exam2021/CMakeFiles/2021-exam4.dir/exam4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2021-exam4.dir/exam4.c.i"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/wanglei/Desktop/hello-world/6.mpi/exam2021/exam4.c > CMakeFiles/2021-exam4.dir/exam4.c.i

exam2021/CMakeFiles/2021-exam4.dir/exam4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2021-exam4.dir/exam4.c.s"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/wanglei/Desktop/hello-world/6.mpi/exam2021/exam4.c -o CMakeFiles/2021-exam4.dir/exam4.c.s

# Object files for target 2021-exam4
2021__exam4_OBJECTS = \
"CMakeFiles/2021-exam4.dir/exam4.c.o"

# External object files for target 2021-exam4
2021__exam4_EXTERNAL_OBJECTS =

exam2021/2021-exam4: exam2021/CMakeFiles/2021-exam4.dir/exam4.c.o
exam2021/2021-exam4: exam2021/CMakeFiles/2021-exam4.dir/build.make
exam2021/2021-exam4: /usr/local/Cellar/open-mpi/4.1.2/lib/libmpi.dylib
exam2021/2021-exam4: exam2021/CMakeFiles/2021-exam4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 2021-exam4"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2021-exam4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
exam2021/CMakeFiles/2021-exam4.dir/build: exam2021/2021-exam4

.PHONY : exam2021/CMakeFiles/2021-exam4.dir/build

exam2021/CMakeFiles/2021-exam4.dir/clean:
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 && $(CMAKE_COMMAND) -P CMakeFiles/2021-exam4.dir/cmake_clean.cmake
.PHONY : exam2021/CMakeFiles/2021-exam4.dir/clean

exam2021/CMakeFiles/2021-exam4.dir/depend:
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wanglei/Desktop/hello-world/6.mpi /Users/wanglei/Desktop/hello-world/6.mpi/exam2021 /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021 /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/exam2021/CMakeFiles/2021-exam4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exam2021/CMakeFiles/2021-exam4.dir/depend
