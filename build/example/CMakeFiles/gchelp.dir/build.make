# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\C++\Cpp_Project\GcServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\C++\Cpp_Project\GcServer\build

# Include any dependencies generated for this target.
include example/CMakeFiles/gchelp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/gchelp.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/gchelp.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/gchelp.dir/flags.make

example/CMakeFiles/gchelp.dir/codegen:
.PHONY : example/CMakeFiles/gchelp.dir/codegen

example/CMakeFiles/gchelp.dir/help.cpp.obj: example/CMakeFiles/gchelp.dir/flags.make
example/CMakeFiles/gchelp.dir/help.cpp.obj: example/CMakeFiles/gchelp.dir/includes_CXX.rsp
example/CMakeFiles/gchelp.dir/help.cpp.obj: D:/C++/Cpp_Project/GcServer/example/help.cpp
example/CMakeFiles/gchelp.dir/help.cpp.obj: example/CMakeFiles/gchelp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\C++\Cpp_Project\GcServer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/gchelp.dir/help.cpp.obj"
	cd /d D:\C++\Cpp_Project\GcServer\build\example && D:\MINGW\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/gchelp.dir/help.cpp.obj -MF CMakeFiles\gchelp.dir\help.cpp.obj.d -o CMakeFiles\gchelp.dir\help.cpp.obj -c D:\C++\Cpp_Project\GcServer\example\help.cpp

example/CMakeFiles/gchelp.dir/help.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/gchelp.dir/help.cpp.i"
	cd /d D:\C++\Cpp_Project\GcServer\build\example && D:\MINGW\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\Cpp_Project\GcServer\example\help.cpp > CMakeFiles\gchelp.dir\help.cpp.i

example/CMakeFiles/gchelp.dir/help.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/gchelp.dir/help.cpp.s"
	cd /d D:\C++\Cpp_Project\GcServer\build\example && D:\MINGW\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\Cpp_Project\GcServer\example\help.cpp -o CMakeFiles\gchelp.dir\help.cpp.s

# Object files for target gchelp
gchelp_OBJECTS = \
"CMakeFiles/gchelp.dir/help.cpp.obj"

# External object files for target gchelp
gchelp_EXTERNAL_OBJECTS =

D:/C++/Cpp_Project/GcServer/bin/gchelp.exe: example/CMakeFiles/gchelp.dir/help.cpp.obj
D:/C++/Cpp_Project/GcServer/bin/gchelp.exe: example/CMakeFiles/gchelp.dir/build.make
D:/C++/Cpp_Project/GcServer/bin/gchelp.exe: example/CMakeFiles/gchelp.dir/linkLibs.rsp
D:/C++/Cpp_Project/GcServer/bin/gchelp.exe: example/CMakeFiles/gchelp.dir/objects1.rsp
D:/C++/Cpp_Project/GcServer/bin/gchelp.exe: example/CMakeFiles/gchelp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\C++\Cpp_Project\GcServer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable D:\C++\Cpp_Project\GcServer\bin\gchelp.exe"
	cd /d D:\C++\Cpp_Project\GcServer\build\example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gchelp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/gchelp.dir/build: D:/C++/Cpp_Project/GcServer/bin/gchelp.exe
.PHONY : example/CMakeFiles/gchelp.dir/build

example/CMakeFiles/gchelp.dir/clean:
	cd /d D:\C++\Cpp_Project\GcServer\build\example && $(CMAKE_COMMAND) -P CMakeFiles\gchelp.dir\cmake_clean.cmake
.PHONY : example/CMakeFiles/gchelp.dir/clean

example/CMakeFiles/gchelp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\C++\Cpp_Project\GcServer D:\C++\Cpp_Project\GcServer\example D:\C++\Cpp_Project\GcServer\build D:\C++\Cpp_Project\GcServer\build\example D:\C++\Cpp_Project\GcServer\build\example\CMakeFiles\gchelp.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : example/CMakeFiles/gchelp.dir/depend

