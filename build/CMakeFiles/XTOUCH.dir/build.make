# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /home/yanran/Downloads/cmake-3.22.1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/yanran/Downloads/cmake-3.22.1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yanran/X-Touch-Controller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yanran/X-Touch-Controller/build

# Include any dependencies generated for this target.
include CMakeFiles/XTOUCH.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/XTOUCH.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/XTOUCH.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XTOUCH.dir/flags.make

CMakeFiles/XTOUCH.dir/main.cpp.o: CMakeFiles/XTOUCH.dir/flags.make
CMakeFiles/XTOUCH.dir/main.cpp.o: ../main.cpp
CMakeFiles/XTOUCH.dir/main.cpp.o: CMakeFiles/XTOUCH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanran/X-Touch-Controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XTOUCH.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XTOUCH.dir/main.cpp.o -MF CMakeFiles/XTOUCH.dir/main.cpp.o.d -o CMakeFiles/XTOUCH.dir/main.cpp.o -c /home/yanran/X-Touch-Controller/main.cpp

CMakeFiles/XTOUCH.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XTOUCH.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanran/X-Touch-Controller/main.cpp > CMakeFiles/XTOUCH.dir/main.cpp.i

CMakeFiles/XTOUCH.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XTOUCH.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanran/X-Touch-Controller/main.cpp -o CMakeFiles/XTOUCH.dir/main.cpp.s

CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o: CMakeFiles/XTOUCH.dir/flags.make
CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o: ../src/XTouch.cpp
CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o: CMakeFiles/XTOUCH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanran/X-Touch-Controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o -MF CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o.d -o CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o -c /home/yanran/X-Touch-Controller/src/XTouch.cpp

CMakeFiles/XTOUCH.dir/src/XTouch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XTOUCH.dir/src/XTouch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanran/X-Touch-Controller/src/XTouch.cpp > CMakeFiles/XTOUCH.dir/src/XTouch.cpp.i

CMakeFiles/XTOUCH.dir/src/XTouch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XTOUCH.dir/src/XTouch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanran/X-Touch-Controller/src/XTouch.cpp -o CMakeFiles/XTOUCH.dir/src/XTouch.cpp.s

CMakeFiles/XTOUCH.dir/src/Fader.cpp.o: CMakeFiles/XTOUCH.dir/flags.make
CMakeFiles/XTOUCH.dir/src/Fader.cpp.o: ../src/Fader.cpp
CMakeFiles/XTOUCH.dir/src/Fader.cpp.o: CMakeFiles/XTOUCH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanran/X-Touch-Controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/XTOUCH.dir/src/Fader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XTOUCH.dir/src/Fader.cpp.o -MF CMakeFiles/XTOUCH.dir/src/Fader.cpp.o.d -o CMakeFiles/XTOUCH.dir/src/Fader.cpp.o -c /home/yanran/X-Touch-Controller/src/Fader.cpp

CMakeFiles/XTOUCH.dir/src/Fader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XTOUCH.dir/src/Fader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanran/X-Touch-Controller/src/Fader.cpp > CMakeFiles/XTOUCH.dir/src/Fader.cpp.i

CMakeFiles/XTOUCH.dir/src/Fader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XTOUCH.dir/src/Fader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanran/X-Touch-Controller/src/Fader.cpp -o CMakeFiles/XTOUCH.dir/src/Fader.cpp.s

CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o: CMakeFiles/XTOUCH.dir/flags.make
CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o: ../src/ControlParameters.cpp
CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o: CMakeFiles/XTOUCH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanran/X-Touch-Controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o -MF CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o.d -o CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o -c /home/yanran/X-Touch-Controller/src/ControlParameters.cpp

CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanran/X-Touch-Controller/src/ControlParameters.cpp > CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.i

CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanran/X-Touch-Controller/src/ControlParameters.cpp -o CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.s

# Object files for target XTOUCH
XTOUCH_OBJECTS = \
"CMakeFiles/XTOUCH.dir/main.cpp.o" \
"CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o" \
"CMakeFiles/XTOUCH.dir/src/Fader.cpp.o" \
"CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o"

# External object files for target XTOUCH
XTOUCH_EXTERNAL_OBJECTS =

XTOUCH: CMakeFiles/XTOUCH.dir/main.cpp.o
XTOUCH: CMakeFiles/XTOUCH.dir/src/XTouch.cpp.o
XTOUCH: CMakeFiles/XTOUCH.dir/src/Fader.cpp.o
XTOUCH: CMakeFiles/XTOUCH.dir/src/ControlParameters.cpp.o
XTOUCH: CMakeFiles/XTOUCH.dir/build.make
XTOUCH: CMakeFiles/XTOUCH.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yanran/X-Touch-Controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable XTOUCH"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XTOUCH.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XTOUCH.dir/build: XTOUCH
.PHONY : CMakeFiles/XTOUCH.dir/build

CMakeFiles/XTOUCH.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XTOUCH.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XTOUCH.dir/clean

CMakeFiles/XTOUCH.dir/depend:
	cd /home/yanran/X-Touch-Controller/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanran/X-Touch-Controller /home/yanran/X-Touch-Controller /home/yanran/X-Touch-Controller/build /home/yanran/X-Touch-Controller/build /home/yanran/X-Touch-Controller/build/CMakeFiles/XTOUCH.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XTOUCH.dir/depend

