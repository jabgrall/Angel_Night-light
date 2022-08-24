cmake_minimum_required(VERSION 3.3)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Choose the type of build, options are: Debug Release")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/compiler/toolchain-arm-none-eabi.cmake" CACHE INTERNAL "Path to the cmake file of the compiler.")

# set the project name
project(Angel)


set(STM32_DEVICE "STM32F103C6T6A")
set(STM32_TARGET "stm32/f1")
set(STM32_CPU_FREQ  "72000000")


#Add libopencm3 in order to prepare compiler for the device
#git clone https://github.com/libopencm3/libopencm3.git
set(ENV{EXTRA_LIBS} "libopencm3")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/libopencm3")


#Add sub directory for source files
add_subdirectory("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory("${PROJECT_SOURCE_DIR}/src")

message(STATUS "Cross-Compiling : ${CMAKE_CROSSCOMPILING}")
