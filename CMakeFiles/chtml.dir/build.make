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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/users/pedro/Documents/Projetos/Packages/chtml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/users/pedro/Documents/Projetos/Packages/chtml

# Include any dependencies generated for this target.
include CMakeFiles/chtml.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chtml.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chtml.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chtml.dir/flags.make

CMakeFiles/chtml.dir/src/tokenizer.c.o: CMakeFiles/chtml.dir/flags.make
CMakeFiles/chtml.dir/src/tokenizer.c.o: src/tokenizer.c
CMakeFiles/chtml.dir/src/tokenizer.c.o: CMakeFiles/chtml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/pedro/Documents/Projetos/Packages/chtml/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/chtml.dir/src/tokenizer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/chtml.dir/src/tokenizer.c.o -MF CMakeFiles/chtml.dir/src/tokenizer.c.o.d -o CMakeFiles/chtml.dir/src/tokenizer.c.o -c /mnt/c/users/pedro/Documents/Projetos/Packages/chtml/src/tokenizer.c

CMakeFiles/chtml.dir/src/tokenizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chtml.dir/src/tokenizer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/users/pedro/Documents/Projetos/Packages/chtml/src/tokenizer.c > CMakeFiles/chtml.dir/src/tokenizer.c.i

CMakeFiles/chtml.dir/src/tokenizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chtml.dir/src/tokenizer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/users/pedro/Documents/Projetos/Packages/chtml/src/tokenizer.c -o CMakeFiles/chtml.dir/src/tokenizer.c.s

# Object files for target chtml
chtml_OBJECTS = \
"CMakeFiles/chtml.dir/src/tokenizer.c.o"

# External object files for target chtml
chtml_EXTERNAL_OBJECTS =

chtml: CMakeFiles/chtml.dir/src/tokenizer.c.o
chtml: CMakeFiles/chtml.dir/build.make
chtml: CMakeFiles/chtml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/users/pedro/Documents/Projetos/Packages/chtml/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable chtml"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chtml.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chtml.dir/build: chtml
.PHONY : CMakeFiles/chtml.dir/build

CMakeFiles/chtml.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chtml.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chtml.dir/clean

CMakeFiles/chtml.dir/depend:
	cd /mnt/c/users/pedro/Documents/Projetos/Packages/chtml && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/users/pedro/Documents/Projetos/Packages/chtml /mnt/c/users/pedro/Documents/Projetos/Packages/chtml /mnt/c/users/pedro/Documents/Projetos/Packages/chtml /mnt/c/users/pedro/Documents/Projetos/Packages/chtml /mnt/c/users/pedro/Documents/Projetos/Packages/chtml/CMakeFiles/chtml.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chtml.dir/depend
