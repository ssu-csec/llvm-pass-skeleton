# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/tpghks/Workspace/pass1/legacyPM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tpghks/Workspace/pass1/legacyPM/build

# Include any dependencies generated for this target.
include CMakeFiles/DFApass.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DFApass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DFApass.dir/flags.make

CMakeFiles/DFApass.dir/src/DFApass.cpp.o: CMakeFiles/DFApass.dir/flags.make
CMakeFiles/DFApass.dir/src/DFApass.cpp.o: ../src/DFApass.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tpghks/Workspace/pass1/legacyPM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DFApass.dir/src/DFApass.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DFApass.dir/src/DFApass.cpp.o -c /home/tpghks/Workspace/pass1/legacyPM/src/DFApass.cpp

CMakeFiles/DFApass.dir/src/DFApass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DFApass.dir/src/DFApass.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tpghks/Workspace/pass1/legacyPM/src/DFApass.cpp > CMakeFiles/DFApass.dir/src/DFApass.cpp.i

CMakeFiles/DFApass.dir/src/DFApass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DFApass.dir/src/DFApass.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tpghks/Workspace/pass1/legacyPM/src/DFApass.cpp -o CMakeFiles/DFApass.dir/src/DFApass.cpp.s

CMakeFiles/DFApass.dir/src/dfa-support.cpp.o: CMakeFiles/DFApass.dir/flags.make
CMakeFiles/DFApass.dir/src/dfa-support.cpp.o: ../src/dfa-support.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tpghks/Workspace/pass1/legacyPM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DFApass.dir/src/dfa-support.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DFApass.dir/src/dfa-support.cpp.o -c /home/tpghks/Workspace/pass1/legacyPM/src/dfa-support.cpp

CMakeFiles/DFApass.dir/src/dfa-support.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DFApass.dir/src/dfa-support.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tpghks/Workspace/pass1/legacyPM/src/dfa-support.cpp > CMakeFiles/DFApass.dir/src/dfa-support.cpp.i

CMakeFiles/DFApass.dir/src/dfa-support.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DFApass.dir/src/dfa-support.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tpghks/Workspace/pass1/legacyPM/src/dfa-support.cpp -o CMakeFiles/DFApass.dir/src/dfa-support.cpp.s

# Object files for target DFApass
DFApass_OBJECTS = \
"CMakeFiles/DFApass.dir/src/DFApass.cpp.o" \
"CMakeFiles/DFApass.dir/src/dfa-support.cpp.o"

# External object files for target DFApass
DFApass_EXTERNAL_OBJECTS =

libDFApass.so: CMakeFiles/DFApass.dir/src/DFApass.cpp.o
libDFApass.so: CMakeFiles/DFApass.dir/src/dfa-support.cpp.o
libDFApass.so: CMakeFiles/DFApass.dir/build.make
libDFApass.so: CMakeFiles/DFApass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tpghks/Workspace/pass1/legacyPM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libDFApass.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DFApass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DFApass.dir/build: libDFApass.so

.PHONY : CMakeFiles/DFApass.dir/build

CMakeFiles/DFApass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DFApass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DFApass.dir/clean

CMakeFiles/DFApass.dir/depend:
	cd /home/tpghks/Workspace/pass1/legacyPM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tpghks/Workspace/pass1/legacyPM /home/tpghks/Workspace/pass1/legacyPM /home/tpghks/Workspace/pass1/legacyPM/build /home/tpghks/Workspace/pass1/legacyPM/build /home/tpghks/Workspace/pass1/legacyPM/build/CMakeFiles/DFApass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DFApass.dir/depend

