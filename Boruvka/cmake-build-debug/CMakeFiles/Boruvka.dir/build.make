# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\rat91\CLionProjects\Boruvka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Boruvka.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Boruvka.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Boruvka.dir/flags.make

CMakeFiles/Boruvka.dir/main.cpp.obj: CMakeFiles/Boruvka.dir/flags.make
CMakeFiles/Boruvka.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Boruvka.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Boruvka.dir\main.cpp.obj -c C:\Users\rat91\CLionProjects\Boruvka\main.cpp

CMakeFiles/Boruvka.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boruvka.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\rat91\CLionProjects\Boruvka\main.cpp > CMakeFiles\Boruvka.dir\main.cpp.i

CMakeFiles/Boruvka.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boruvka.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\rat91\CLionProjects\Boruvka\main.cpp -o CMakeFiles\Boruvka.dir\main.cpp.s

# Object files for target Boruvka
Boruvka_OBJECTS = \
"CMakeFiles/Boruvka.dir/main.cpp.obj"

# External object files for target Boruvka
Boruvka_EXTERNAL_OBJECTS =

Boruvka.exe: CMakeFiles/Boruvka.dir/main.cpp.obj
Boruvka.exe: CMakeFiles/Boruvka.dir/build.make
Boruvka.exe: CMakeFiles/Boruvka.dir/linklibs.rsp
Boruvka.exe: CMakeFiles/Boruvka.dir/objects1.rsp
Boruvka.exe: CMakeFiles/Boruvka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Boruvka.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Boruvka.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Boruvka.dir/build: Boruvka.exe

.PHONY : CMakeFiles/Boruvka.dir/build

CMakeFiles/Boruvka.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Boruvka.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Boruvka.dir/clean

CMakeFiles/Boruvka.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\rat91\CLionProjects\Boruvka C:\Users\rat91\CLionProjects\Boruvka C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug C:\Users\rat91\CLionProjects\Boruvka\cmake-build-debug\CMakeFiles\Boruvka.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Boruvka.dir/depend

