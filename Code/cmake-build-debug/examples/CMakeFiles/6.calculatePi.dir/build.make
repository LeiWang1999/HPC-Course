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
include examples/CMakeFiles/6.calculatePi.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/6.calculatePi.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/6.calculatePi.dir/flags.make

examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o: examples/CMakeFiles/6.calculatePi.dir/flags.make
examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o: ../examples/6.calculatePi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o -c /Users/wanglei/Desktop/hello-world/6.mpi/examples/6.calculatePi.cpp

examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.i"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wanglei/Desktop/hello-world/6.mpi/examples/6.calculatePi.cpp > CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.i

examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.s"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wanglei/Desktop/hello-world/6.mpi/examples/6.calculatePi.cpp -o CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.s

# Object files for target 6.calculatePi
6_calculatePi_OBJECTS = \
"CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o"

# External object files for target 6.calculatePi
6_calculatePi_EXTERNAL_OBJECTS =

examples/6.calculatePi: examples/CMakeFiles/6.calculatePi.dir/6.calculatePi.cpp.o
examples/6.calculatePi: examples/CMakeFiles/6.calculatePi.dir/build.make
examples/6.calculatePi: /usr/local/Cellar/open-mpi/4.1.2/lib/libmpi.dylib
examples/6.calculatePi: examples/CMakeFiles/6.calculatePi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 6.calculatePi"
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/6.calculatePi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/6.calculatePi.dir/build: examples/6.calculatePi

.PHONY : examples/CMakeFiles/6.calculatePi.dir/build

examples/CMakeFiles/6.calculatePi.dir/clean:
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples && $(CMAKE_COMMAND) -P CMakeFiles/6.calculatePi.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/6.calculatePi.dir/clean

examples/CMakeFiles/6.calculatePi.dir/depend:
	cd /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wanglei/Desktop/hello-world/6.mpi /Users/wanglei/Desktop/hello-world/6.mpi/examples /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples /Users/wanglei/Desktop/hello-world/6.mpi/cmake-build-debug/examples/CMakeFiles/6.calculatePi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/6.calculatePi.dir/depend
