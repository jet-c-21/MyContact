# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/puff/devWorkspace/myIDE/clion-2019.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/puff/devWorkspace/myIDE/clion-2019.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/puff/devWorkspace/SIDE-PROJECT/MyContact

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.cpp.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/app.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/main.cpp.o -c /home/puff/devWorkspace/SIDE-PROJECT/MyContact/main.cpp

CMakeFiles/app.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/puff/devWorkspace/SIDE-PROJECT/MyContact/main.cpp > CMakeFiles/app.dir/main.cpp.i

CMakeFiles/app.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/puff/devWorkspace/SIDE-PROJECT/MyContact/main.cpp -o CMakeFiles/app.dir/main.cpp.s

CMakeFiles/app.dir/src/contact.cpp.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/src/contact.cpp.o: ../src/contact.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/app.dir/src/contact.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/src/contact.cpp.o -c /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/contact.cpp

CMakeFiles/app.dir/src/contact.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/src/contact.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/contact.cpp > CMakeFiles/app.dir/src/contact.cpp.i

CMakeFiles/app.dir/src/contact.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/src/contact.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/contact.cpp -o CMakeFiles/app.dir/src/contact.cpp.s

CMakeFiles/app.dir/src/mycontact.cpp.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/src/mycontact.cpp.o: ../src/mycontact.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/app.dir/src/mycontact.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/src/mycontact.cpp.o -c /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/mycontact.cpp

CMakeFiles/app.dir/src/mycontact.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/src/mycontact.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/mycontact.cpp > CMakeFiles/app.dir/src/mycontact.cpp.i

CMakeFiles/app.dir/src/mycontact.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/src/mycontact.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/puff/devWorkspace/SIDE-PROJECT/MyContact/src/mycontact.cpp -o CMakeFiles/app.dir/src/mycontact.cpp.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.cpp.o" \
"CMakeFiles/app.dir/src/contact.cpp.o" \
"CMakeFiles/app.dir/src/mycontact.cpp.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/main.cpp.o
app: CMakeFiles/app.dir/src/contact.cpp.o
app: CMakeFiles/app.dir/src/mycontact.cpp.o
app: CMakeFiles/app.dir/build.make
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app

.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/puff/devWorkspace/SIDE-PROJECT/MyContact /home/puff/devWorkspace/SIDE-PROJECT/MyContact /home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug /home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug /home/puff/devWorkspace/SIDE-PROJECT/MyContact/cmake-build-debug/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend

