# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master

# Include any dependencies generated for this target.
include examples/hub/CMakeFiles/sub.dir/depend.make

# Include the progress variables for this target.
include examples/hub/CMakeFiles/sub.dir/progress.make

# Include the compile flags for this target's objects.
include examples/hub/CMakeFiles/sub.dir/flags.make

examples/hub/CMakeFiles/sub.dir/sub.cc.o: examples/hub/CMakeFiles/sub.dir/flags.make
examples/hub/CMakeFiles/sub.dir/sub.cc.o: examples/hub/sub.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/hub/CMakeFiles/sub.dir/sub.cc.o"
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sub.dir/sub.cc.o -c /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub/sub.cc

examples/hub/CMakeFiles/sub.dir/sub.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sub.dir/sub.cc.i"
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub/sub.cc > CMakeFiles/sub.dir/sub.cc.i

examples/hub/CMakeFiles/sub.dir/sub.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sub.dir/sub.cc.s"
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub/sub.cc -o CMakeFiles/sub.dir/sub.cc.s

examples/hub/CMakeFiles/sub.dir/sub.cc.o.requires:

.PHONY : examples/hub/CMakeFiles/sub.dir/sub.cc.o.requires

examples/hub/CMakeFiles/sub.dir/sub.cc.o.provides: examples/hub/CMakeFiles/sub.dir/sub.cc.o.requires
	$(MAKE) -f examples/hub/CMakeFiles/sub.dir/build.make examples/hub/CMakeFiles/sub.dir/sub.cc.o.provides.build
.PHONY : examples/hub/CMakeFiles/sub.dir/sub.cc.o.provides

examples/hub/CMakeFiles/sub.dir/sub.cc.o.provides.build: examples/hub/CMakeFiles/sub.dir/sub.cc.o


# Object files for target sub
sub_OBJECTS = \
"CMakeFiles/sub.dir/sub.cc.o"

# External object files for target sub
sub_EXTERNAL_OBJECTS =

bin/sub: examples/hub/CMakeFiles/sub.dir/sub.cc.o
bin/sub: examples/hub/CMakeFiles/sub.dir/build.make
bin/sub: lib/libmuduo_pubsub.a
bin/sub: lib/libmuduo_net.a
bin/sub: lib/libmuduo_base.a
bin/sub: examples/hub/CMakeFiles/sub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/sub"
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/hub/CMakeFiles/sub.dir/build: bin/sub

.PHONY : examples/hub/CMakeFiles/sub.dir/build

examples/hub/CMakeFiles/sub.dir/requires: examples/hub/CMakeFiles/sub.dir/sub.cc.o.requires

.PHONY : examples/hub/CMakeFiles/sub.dir/requires

examples/hub/CMakeFiles/sub.dir/clean:
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub && $(CMAKE_COMMAND) -P CMakeFiles/sub.dir/cmake_clean.cmake
.PHONY : examples/hub/CMakeFiles/sub.dir/clean

examples/hub/CMakeFiles/sub.dir/depend:
	cd /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub/CMakeFiles/sub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/hub/CMakeFiles/sub.dir/depend
