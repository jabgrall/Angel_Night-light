#Toolchain definition


set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_VERSION   1)
set(CMAKE_SYSTEM_PROCESSOR ARM)


set(TOOL_CHAIN_PREFIX arm-none-eabi)
set(TOOLCHAIN_DIR ${PROJECT_SOURCE_DIR}/compiler)
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_DIR}/bin)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_DIR}/${TOOL_CHAIN_PREFIX}/lib)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_DIR}/${TOOL_CHAIN_PREFIX}/include)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# which compilers to use for C and C++
SET(CMAKE_AR               ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-gcc-ar)
SET(CMAKE_RANLIB           ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-gcc-ranlib)
SET(CMAKE_LD               ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-ld)
set(CMAKE_C_COMPILER       ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER     ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER     ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-as)
set(CMAKE_OBJCOPY     	   ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-objcopy CACHE INTERNAL "objcopy command")
set(CMAKE_OBJDUMP     	   ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-objdump CACHE INTERNAL "objdump command")
set(CMAKE_GDB              ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-gdb)
set(CMAKE_SIZE              ${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}-size)


#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

set(COMPILER_OPTIONS "-ffunction-sections -fdata-sections -Wall -Wextra -Wredundant-decls -Wshadow -fno-common")


set(CMAKE_C_FLAGS   "${COMPILER_OPTIONS} -std=gnu99 -Wimplicit-function-declaration -Wmissing-prototypes -Wstrict-prototypes" CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${COMPILER_OPTIONS} -std=c++11 -fno-use-cxa-atexit -fno-rtti -fno-exceptions" CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${COMPILER_OPTIONS} -x assembler-with-cpp " CACHE INTERNAL "ASM Compiler options")


# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -nostartfiles --static --specs=nano.specs --specs=nosys.specs -Wl,--start-group -lc -lgcc -lm -lstdc++ -lnosys -Wl,--end-group -Wl,--print-memory-usage" CACHE INTERNAL "Linker options")


#---------------------------------------------------------------------------------------
# Set debug/release build configuration Options
#---------------------------------------------------------------------------------------

# Options for DEBUG build
# -Og   Enables optimizations that do not interfere with debugging.
# -g    Produce debugging information in the operating system’s native format.
set(CMAKE_C_FLAGS_DEBUG "-Og -g2 -ggdb2" CACHE INTERNAL "C Compiler options for debug build type")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g2 -ggdb2" CACHE INTERNAL "C++ Compiler options for debug build type")
set(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "ASM Compiler options for debug build type")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")

# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
set(CMAKE_C_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C Compiler options for release build type")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C++ Compiler options for release build type")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build type")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "Linker options for release build type")


set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_DIR}/${TOOL_CHAIN_PREFIX} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
