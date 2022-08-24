# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/jabgrall/Bureau/test_projet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jabgrall/Bureau/test_projet/build

# Include any dependencies generated for this target.
include lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/progress.make

# Include the compile flags for this target's objects.
include lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj: ../lib/FreeRTOS-Kernel/croutine.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj -MF CMakeFiles/freertos_kernel.dir/croutine.c.obj.d -o CMakeFiles/freertos_kernel.dir/croutine.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/croutine.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/croutine.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/croutine.c > CMakeFiles/freertos_kernel.dir/croutine.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/croutine.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/croutine.c -o CMakeFiles/freertos_kernel.dir/croutine.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj: ../lib/FreeRTOS-Kernel/event_groups.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj -MF CMakeFiles/freertos_kernel.dir/event_groups.c.obj.d -o CMakeFiles/freertos_kernel.dir/event_groups.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/event_groups.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/event_groups.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/event_groups.c > CMakeFiles/freertos_kernel.dir/event_groups.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/event_groups.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/event_groups.c -o CMakeFiles/freertos_kernel.dir/event_groups.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj: ../lib/FreeRTOS-Kernel/list.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj -MF CMakeFiles/freertos_kernel.dir/list.c.obj.d -o CMakeFiles/freertos_kernel.dir/list.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/list.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/list.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/list.c > CMakeFiles/freertos_kernel.dir/list.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/list.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/list.c -o CMakeFiles/freertos_kernel.dir/list.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj: ../lib/FreeRTOS-Kernel/queue.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj -MF CMakeFiles/freertos_kernel.dir/queue.c.obj.d -o CMakeFiles/freertos_kernel.dir/queue.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/queue.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/queue.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/queue.c > CMakeFiles/freertos_kernel.dir/queue.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/queue.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/queue.c -o CMakeFiles/freertos_kernel.dir/queue.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj: ../lib/FreeRTOS-Kernel/stream_buffer.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj -MF CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj.d -o CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/stream_buffer.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/stream_buffer.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/stream_buffer.c > CMakeFiles/freertos_kernel.dir/stream_buffer.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/stream_buffer.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/stream_buffer.c -o CMakeFiles/freertos_kernel.dir/stream_buffer.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj: ../lib/FreeRTOS-Kernel/tasks.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj -MF CMakeFiles/freertos_kernel.dir/tasks.c.obj.d -o CMakeFiles/freertos_kernel.dir/tasks.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/tasks.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/tasks.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/tasks.c > CMakeFiles/freertos_kernel.dir/tasks.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/tasks.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/tasks.c -o CMakeFiles/freertos_kernel.dir/tasks.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj: ../lib/FreeRTOS-Kernel/timers.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj -MF CMakeFiles/freertos_kernel.dir/timers.c.obj.d -o CMakeFiles/freertos_kernel.dir/timers.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/timers.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/timers.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/timers.c > CMakeFiles/freertos_kernel.dir/timers.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/timers.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/timers.c -o CMakeFiles/freertos_kernel.dir/timers.c.s

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/flags.make
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj: ../lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj -MF CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj.d -o CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj -c /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.i"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c > CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.i

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.s"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && /home/jabgrall/Bureau/test_projet/compiler/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c -o CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.s

# Object files for target freertos_kernel
freertos_kernel_OBJECTS = \
"CMakeFiles/freertos_kernel.dir/croutine.c.obj" \
"CMakeFiles/freertos_kernel.dir/event_groups.c.obj" \
"CMakeFiles/freertos_kernel.dir/list.c.obj" \
"CMakeFiles/freertos_kernel.dir/queue.c.obj" \
"CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj" \
"CMakeFiles/freertos_kernel.dir/tasks.c.obj" \
"CMakeFiles/freertos_kernel.dir/timers.c.obj" \
"CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj"

# External object files for target freertos_kernel
freertos_kernel_EXTERNAL_OBJECTS =

lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/croutine.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/event_groups.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/list.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/queue.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/stream_buffer.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/tasks.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/timers.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/portable/MemMang/heap_4.c.obj
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/build.make
lib/FreeRTOS-Kernel/libfreertos_kernel.a: lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jabgrall/Bureau/test_projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C static library libfreertos_kernel.a"
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && $(CMAKE_COMMAND) -P CMakeFiles/freertos_kernel.dir/cmake_clean_target.cmake
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freertos_kernel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/build: lib/FreeRTOS-Kernel/libfreertos_kernel.a
.PHONY : lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/build

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/clean:
	cd /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel && $(CMAKE_COMMAND) -P CMakeFiles/freertos_kernel.dir/cmake_clean.cmake
.PHONY : lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/clean

lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/depend:
	cd /home/jabgrall/Bureau/test_projet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jabgrall/Bureau/test_projet /home/jabgrall/Bureau/test_projet/lib/FreeRTOS-Kernel /home/jabgrall/Bureau/test_projet/build /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel /home/jabgrall/Bureau/test_projet/build/lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/FreeRTOS-Kernel/CMakeFiles/freertos_kernel.dir/depend

