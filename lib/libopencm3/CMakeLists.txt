set(LIBOPENCM3_DIR ${CMAKE_CURRENT_SOURCE_DIR/libopencm3})

add_custom_target(build_libopencm3 COMMAND make PREFIX=${TOOLCHAIN_BIN_DIR}/${TOOL_CHAIN_PREFIX}- TARGETS=${STM32_TARGET} DEVICE=${STM32_DEVICE} all WORKING_DIRECTORY ${LIBOPENCM3_DIR})

add_library(libopencm3 STATIC IMPORTED GLOBAL)

set(ENV{LDSCRIPT} "${LIBOPENCM3_DIR}/ld/generated.${STM32_DEVICE}.ld")
set(DEVICE_DATA "${LIBOPENCM3_DIR}/ld/devices.data")

execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} FAMILY WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_family)
execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} SUBFAMILY WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_subfamily)
execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} CPU WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_cpu)
execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} FPU WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_fpu)
execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} CPPFLAGS WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_cppflags)

message(STATUS "genlink_family : ${genlink_family}")
message(STATUS "genlink_subfamily : ${genlink_subfamily}")
message(STATUS "genlink_cpu : ${genlink_cpu}")
message(STATUS "genlink_fpu : ${genlink_fpu}")
message(STATUS "genlink_cppflags : ${genlink_cppflags}")

set(arch_flags "-mcpu=${genlink_cpu}")

set(tmp_test_list cortex-m0 cortex-m0plus cortex-m3 cortex-m4 cortex-m7)
if(genlink_cpu IN_LIST tmp_test_list)
	set(arch_flags "${arch_flags} -mthumb")
endif()

if(${genlink_fpu} STREQUAL "soft")
	set(arch_flags "${arch_flags} -msoft-float")
elseif(${genlink_fpu} STREQUAL "hard-fpv4-sp-d16")
	set(arch_flags "${arch_flags} -mfloat-abi=hard -mfpu=fpv4-sp-d16")
elseif(${genlink_fpu} STREQUAL "hard-fpv5-sp-d16")
	set(arch_flags "${arch_flags} -mfloat-abi=hard -mfpu=fpv5-sp-d16")
else()
	message(WARNING "No match for the FPU flags")
endif()

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${genlink_cppflags} ${arch_flags} -DF_CPU=${STM32_CPU_FREQ}L" CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${genlink_cppflags} ${arch_flags} -DF_CPU=${STM32_CPU_FREQ}L" CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${genlink_cppflags} ${arch_flags} -DF_CPU=${STM32_CPU_FREQ}L" CACHE INTERNAL "ASM Compiler options")


#Generate link script file
execute_process(COMMAND ${LIBOPENCM3_DIR}/scripts/genlink.py ${DEVICE_DATA} ${STM32_DEVICE} DEFS WORKING_DIRECTORY ${LIBOPENCM3_DIR} OUTPUT_VARIABLE genlink_defs)
set(tmp_args "${arch_flags} ${genlink_defs}")
string(REPLACE " " ";" tmp_args ${tmp_args})
message(STATUS "\nGenerate LD script : $ENV{LDSCRIPT}")
execute_process(COMMAND ${CMAKE_C_COMPILER} ${tmp_args} -P -E ${LIBOPENCM3_DIR}/ld/linker.ld.S -o $ENV{LDSCRIPT} WORKING_DIRECTORY ${LIBOPENCM3_DIR}/ld OUTPUT_VARIABLE tmp)

add_dependencies(libopencm3 build_libopencm3)
set(tmp_args "${arch_flags}")
string(REPLACE " " ";" tmp_args ${tmp_args})
target_link_options(libopencm3 INTERFACE "-T$ENV{LDSCRIPT}" ${tmp_args}) 
set_property(TARGET libopencm3 PROPERTY IMPORTED_LOCATION "${LIBOPENCM3_DIR}/lib/libopencm3_${genlink_family}.a")

#Todo: remove SYSTEM option
target_include_directories(libopencm3 SYSTEM INTERFACE ${LIBOPENCM3_DIR}/include)

message(STATUS "${STATIC_LIBRARY_OPTIONS} ${STATIC_LIBRARY_FLAGS}")
