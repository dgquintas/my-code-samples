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
include tests/gmock/CMakeFiles/gmock_main.dir/depend.make

# Include the progress variables for this target.
include tests/gmock/CMakeFiles/gmock_main.dir/progress.make

# Include the compile flags for this target's objects.
include tests/gmock/CMakeFiles/gmock_main.dir/flags.make

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o: tests/gmock/CMakeFiles/gmock_main.dir/flags.make
tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o: ../tests/gmock/gtest/src/gtest-all.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o -c /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/gtest/src/gtest-all.cc

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.i"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/gtest/src/gtest-all.cc > CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.i

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.s"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/gtest/src/gtest-all.cc -o CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.s

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.requires:
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.requires

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.provides: tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.requires
	$(MAKE) -f tests/gmock/CMakeFiles/gmock_main.dir/build.make tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.provides.build
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.provides

tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.provides.build: tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: tests/gmock/CMakeFiles/gmock_main.dir/flags.make
tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o: ../tests/gmock/src/gmock-all.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.o -c /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock-all.cc

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock-all.cc.i"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock-all.cc > CMakeFiles/gmock_main.dir/src/gmock-all.cc.i

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock-all.cc.s"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock-all.cc -o CMakeFiles/gmock_main.dir/src/gmock-all.cc.s

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires:
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
	$(MAKE) -f tests/gmock/CMakeFiles/gmock_main.dir/build.make tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.provides.build: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: tests/gmock/CMakeFiles/gmock_main.dir/flags.make
tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: ../tests/gmock/src/gmock_main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock_main.cc

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock_main.cc.i"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock_main.cc > CMakeFiles/gmock_main.dir/src/gmock_main.cc.i

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock_main.cc.s"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock/src/gmock_main.cc -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.s

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires:
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires
	$(MAKE) -f tests/gmock/CMakeFiles/gmock_main.dir/build.make tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides

tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.provides.build: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o

# Object files for target gmock_main
gmock_main_OBJECTS = \
"CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock-all.cc.o" \
"CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"

# External object files for target gmock_main
gmock_main_EXTERNAL_OBJECTS =

tests/gmock/libgmock_main.a: tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o
tests/gmock/libgmock_main.a: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o
tests/gmock/libgmock_main.a: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
tests/gmock/libgmock_main.a: tests/gmock/CMakeFiles/gmock_main.dir/build.make
tests/gmock/libgmock_main.a: tests/gmock/CMakeFiles/gmock_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libgmock_main.a"
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/gmock/CMakeFiles/gmock_main.dir/build: tests/gmock/libgmock_main.a
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/build

tests/gmock/CMakeFiles/gmock_main.dir/requires: tests/gmock/CMakeFiles/gmock_main.dir/gtest/src/gtest-all.cc.o.requires
tests/gmock/CMakeFiles/gmock_main.dir/requires: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock-all.cc.o.requires
tests/gmock/CMakeFiles/gmock_main.dir/requires: tests/gmock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o.requires
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/requires

tests/gmock/CMakeFiles/gmock_main.dir/clean:
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean.cmake
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/clean

tests/gmock/CMakeFiles/gmock_main.dir/depend:
	cd /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/tests/gmock /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock /home/dgquintas/Dropbox/samples/algorithms/dynamic_programming/linear_partitioning/cpp/linear_partitioning/build/tests/gmock/CMakeFiles/gmock_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/gmock/CMakeFiles/gmock_main.dir/depend

