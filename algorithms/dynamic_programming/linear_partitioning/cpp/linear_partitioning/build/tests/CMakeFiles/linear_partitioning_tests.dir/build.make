# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_SOURCE_DIR = /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/linear_partitioning_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/linear_partitioning_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/linear_partitioning_tests.dir/flags.make

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o: tests/CMakeFiles/linear_partitioning_tests.dir/flags.make
tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o: ../tests/linear_partitioning_tests.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o -c /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/linear_partitioning_tests.cpp

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.i"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/linear_partitioning_tests.cpp > CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.i

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.s"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/linear_partitioning_tests.cpp -o CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.s

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.requires:
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.requires

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.provides: tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/linear_partitioning_tests.dir/build.make tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.provides.build
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.provides

tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.provides.build: tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o

# Object files for target linear_partitioning_tests
linear_partitioning_tests_OBJECTS = \
"CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o"

# External object files for target linear_partitioning_tests
linear_partitioning_tests_EXTERNAL_OBJECTS =

tests/linear_partitioning_tests: tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o
tests/linear_partitioning_tests: tests/CMakeFiles/linear_partitioning_tests.dir/build.make
tests/linear_partitioning_tests: liblinear_partitioning.a
tests/linear_partitioning_tests: tests/gmock/gtest/libgtest.a
tests/linear_partitioning_tests: tests/gmock/gtest/libgtest_main.a
tests/linear_partitioning_tests: tests/gmock/libgmock.a
tests/linear_partitioning_tests: tests/gmock/gtest/libgtest.a
tests/linear_partitioning_tests: tests/CMakeFiles/linear_partitioning_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable linear_partitioning_tests"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linear_partitioning_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/linear_partitioning_tests.dir/build: tests/linear_partitioning_tests
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/build

tests/CMakeFiles/linear_partitioning_tests.dir/requires: tests/CMakeFiles/linear_partitioning_tests.dir/linear_partitioning_tests.cpp.o.requires
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/requires

tests/CMakeFiles/linear_partitioning_tests.dir/clean:
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/linear_partitioning_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/clean

tests/CMakeFiles/linear_partitioning_tests.dir/depend:
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/CMakeFiles/linear_partitioning_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/linear_partitioning_tests.dir/depend
