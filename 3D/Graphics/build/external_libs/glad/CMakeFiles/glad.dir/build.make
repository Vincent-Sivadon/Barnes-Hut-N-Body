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
CMAKE_SOURCE_DIR = /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build

# Include any dependencies generated for this target.
include external_libs/glad/CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include external_libs/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include external_libs/glad/CMakeFiles/glad.dir/flags.make

external_libs/glad/CMakeFiles/glad.dir/glad.c.o: external_libs/glad/CMakeFiles/glad.dir/flags.make
external_libs/glad/CMakeFiles/glad.dir/glad.c.o: ../external_libs/glad/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external_libs/glad/CMakeFiles/glad.dir/glad.c.o"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/glad.c.o   -c /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/glad/glad.c

external_libs/glad/CMakeFiles/glad.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glad.c.i"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/glad/glad.c > CMakeFiles/glad.dir/glad.c.i

external_libs/glad/CMakeFiles/glad.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glad.c.s"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/glad/glad.c -o CMakeFiles/glad.dir/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

external_libs/glad/libglad.so: external_libs/glad/CMakeFiles/glad.dir/glad.c.o
external_libs/glad/libglad.so: external_libs/glad/CMakeFiles/glad.dir/build.make
external_libs/glad/libglad.so: external_libs/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libglad.so"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external_libs/glad/CMakeFiles/glad.dir/build: external_libs/glad/libglad.so

.PHONY : external_libs/glad/CMakeFiles/glad.dir/build

external_libs/glad/CMakeFiles/glad.dir/clean:
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : external_libs/glad/CMakeFiles/glad.dir/clean

external_libs/glad/CMakeFiles/glad.dir/depend:
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/glad /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/glad/CMakeFiles/glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external_libs/glad/CMakeFiles/glad.dir/depend

