# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files (x86)\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files (x86)\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Program Files (x86)\Project\GameProgramProject\Week03"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Week03.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Week03.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Week03.dir/flags.make

CMakeFiles/Week03.dir/main.cpp.obj: CMakeFiles/Week03.dir/flags.make
CMakeFiles/Week03.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Week03.dir/main.cpp.obj"
	D:\mingw-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Week03.dir\main.cpp.obj -c "D:\Program Files (x86)\Project\GameProgramProject\Week03\main.cpp"

CMakeFiles/Week03.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Week03.dir/main.cpp.i"
	D:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Program Files (x86)\Project\GameProgramProject\Week03\main.cpp" > CMakeFiles\Week03.dir\main.cpp.i

CMakeFiles/Week03.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Week03.dir/main.cpp.s"
	D:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Program Files (x86)\Project\GameProgramProject\Week03\main.cpp" -o CMakeFiles\Week03.dir\main.cpp.s

# Object files for target Week03
Week03_OBJECTS = \
"CMakeFiles/Week03.dir/main.cpp.obj"

# External object files for target Week03
Week03_EXTERNAL_OBJECTS =

Week03.exe: CMakeFiles/Week03.dir/main.cpp.obj
Week03.exe: CMakeFiles/Week03.dir/build.make
Week03.exe: CMakeFiles/Week03.dir/linklibs.rsp
Week03.exe: CMakeFiles/Week03.dir/objects1.rsp
Week03.exe: CMakeFiles/Week03.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Week03.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Week03.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Week03.dir/build: Week03.exe

.PHONY : CMakeFiles/Week03.dir/build

CMakeFiles/Week03.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Week03.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Week03.dir/clean

CMakeFiles/Week03.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Program Files (x86)\Project\GameProgramProject\Week03" "D:\Program Files (x86)\Project\GameProgramProject\Week03" "D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug" "D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug" "D:\Program Files (x86)\Project\GameProgramProject\Week03\cmake-build-debug\CMakeFiles\Week03.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Week03.dir/depend
