# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/currency_service.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/currency_service.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/currency_service.dir/flags.make

CMakeFiles/currency_service.dir/currency_service.cpp.o: CMakeFiles/currency_service.dir/flags.make
CMakeFiles/currency_service.dir/currency_service.cpp.o: ../currency_service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/currency_service.dir/currency_service.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/currency_service.dir/currency_service.cpp.o -c "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/currency_service.cpp"

CMakeFiles/currency_service.dir/currency_service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/currency_service.dir/currency_service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/currency_service.cpp" > CMakeFiles/currency_service.dir/currency_service.cpp.i

CMakeFiles/currency_service.dir/currency_service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/currency_service.dir/currency_service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/currency_service.cpp" -o CMakeFiles/currency_service.dir/currency_service.cpp.s

CMakeFiles/currency_service.dir/currency_service.cpp.o.requires:

.PHONY : CMakeFiles/currency_service.dir/currency_service.cpp.o.requires

CMakeFiles/currency_service.dir/currency_service.cpp.o.provides: CMakeFiles/currency_service.dir/currency_service.cpp.o.requires
	$(MAKE) -f CMakeFiles/currency_service.dir/build.make CMakeFiles/currency_service.dir/currency_service.cpp.o.provides.build
.PHONY : CMakeFiles/currency_service.dir/currency_service.cpp.o.provides

CMakeFiles/currency_service.dir/currency_service.cpp.o.provides.build: CMakeFiles/currency_service.dir/currency_service.cpp.o


CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o: CMakeFiles/currency_service.dir/flags.make
CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o: ../src/services/CurrencyService.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o -c "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/src/services/CurrencyService.cpp"

CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/src/services/CurrencyService.cpp" > CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.i

CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/src/services/CurrencyService.cpp" -o CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.s

CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.requires:

.PHONY : CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.requires

CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.provides: CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.requires
	$(MAKE) -f CMakeFiles/currency_service.dir/build.make CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.provides.build
.PHONY : CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.provides

CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.provides.build: CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o


# Object files for target currency_service
currency_service_OBJECTS = \
"CMakeFiles/currency_service.dir/currency_service.cpp.o" \
"CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o"

# External object files for target currency_service
currency_service_EXTERNAL_OBJECTS =

currency_service: CMakeFiles/currency_service.dir/currency_service.cpp.o
currency_service: CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o
currency_service: CMakeFiles/currency_service.dir/build.make
currency_service: CMakeFiles/currency_service.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable currency_service"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/currency_service.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/currency_service.dir/build: currency_service

.PHONY : CMakeFiles/currency_service.dir/build

CMakeFiles/currency_service.dir/requires: CMakeFiles/currency_service.dir/currency_service.cpp.o.requires
CMakeFiles/currency_service.dir/requires: CMakeFiles/currency_service.dir/src/services/CurrencyService.cpp.o.requires

.PHONY : CMakeFiles/currency_service.dir/requires

CMakeFiles/currency_service.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/currency_service.dir/cmake_clean.cmake
.PHONY : CMakeFiles/currency_service.dir/clean

CMakeFiles/currency_service.dir/depend:
	cd "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2" "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2" "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug" "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug" "/home/fedelonghi/Facultad/Tecnicas de Prgramacion Concurrente I/Proyecto2/cmake-build-debug/CMakeFiles/currency_service.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/currency_service.dir/depend

