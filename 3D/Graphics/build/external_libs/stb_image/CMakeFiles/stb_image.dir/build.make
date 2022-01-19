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
include external_libs/stb_image/CMakeFiles/stb_image.dir/depend.make

# Include the progress variables for this target.
include external_libs/stb_image/CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include external_libs/stb_image/CMakeFiles/stb_image.dir/flags.make

external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.o: external_libs/stb_image/CMakeFiles/stb_image.dir/flags.make
external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.o: ../external_libs/stb_image/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.o"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stb_image.dir/stb_image.cpp.o -c /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/stb_image/stb_image.cpp

external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stb_image.dir/stb_image.cpp.i"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/stb_image/stb_image.cpp > CMakeFiles/stb_image.dir/stb_image.cpp.i

external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stb_image.dir/stb_image.cpp.s"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/stb_image/stb_image.cpp -o CMakeFiles/stb_image.dir/stb_image.cpp.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/stb_image.cpp.o"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

external_libs/stb_image/libstb_image.a: external_libs/stb_image/CMakeFiles/stb_image.dir/stb_image.cpp.o
external_libs/stb_image/libstb_image.a: external_libs/stb_image/CMakeFiles/stb_image.dir/build.make
external_libs/stb_image/libstb_image.a: external_libs/stb_image/CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstb_image.a"
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean_target.cmake
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stb_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external_libs/stb_image/CMakeFiles/stb_image.dir/build: external_libs/stb_image/libstb_image.a

.PHONY : external_libs/stb_image/CMakeFiles/stb_image.dir/build

external_libs/stb_image/CMakeFiles/stb_image.dir/clean:
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stb_image.dir/cmake_clean.cmake
.PHONY : external_libs/stb_image/CMakeFiles/stb_image.dir/clean

external_libs/stb_image/CMakeFiles/stb_image.dir/depend:
	cd /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/external_libs/stb_image /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image /home/vincents/Documents/ArchiParallele/NBODY/3D/Graphics/build/external_libs/stb_image/CMakeFiles/stb_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external_libs/stb_image/CMakeFiles/stb_image.dir/depend
