# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /home/dgq/bin/cmake-3.2.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/dgq/bin/cmake-3.2.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests

# Include any dependencies generated for this target.
include CMakeFiles/linear_partitioning_tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linear_partitioning_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linear_partitioning_tests.dir/flags.make

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o: CMakeFiles/linear_partitioning_tests.dir/flags.make
CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o: linear_partitioning_tests.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o -c /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests/linear_partitioning_tests.cpp

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests/linear_partitioning_tests.cpp > CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.i

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests/linear_partitioning_tests.cpp -o CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.s

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.requires:
.PHONY : CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.requires

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.provides: CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.requires
	$(MAKE) -f CMakeFiles/linear_partitioning_tests.dir/build.make CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.provides.build
.PHONY : CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.provides

CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.provides.build: CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o

# Object files for target linear_partitioning_tests
linear_partitioning_tests_OBJECTS = \
"CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o"

# External object files for target linear_partitioning_tests
linear_partitioning_tests_EXTERNAL_OBJECTS =

linear_partitioning_tests: CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o
linear_partitioning_tests: CMakeFiles/linear_partitioning_tests.dir/build.make
linear_partitioning_tests: /usr/lib/libgtest.a
linear_partitioning_tests: /usr/lib/libgtest_main.a
linear_partitioning_tests: CMakeFiles/linear_partitioning_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable linear_partitioning_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linear_partitioning_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linear_partitioning_tests.dir/build: linear_partitioning_tests
.PHONY : CMakeFiles/linear_partitioning_tests.dir/build

CMakeFiles/linear_partitioning_tests.dir/requires: CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.o.requires
.PHONY : CMakeFiles/linear_partitioning_tests.dir/requires

CMakeFiles/linear_partitioning_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linear_partitioning_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linear_partitioning_tests.dir/clean

CMakeFiles/linear_partitioning_tests.dir/depend:
	cd /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests /home/dgq/vbox/Dropbox/samples/cmake/linear_partitioning/tests/CMakeFiles/linear_partitioning_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/linear_partitioning_tests.dir/depend

