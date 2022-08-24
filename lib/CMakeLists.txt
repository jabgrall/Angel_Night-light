#Add ADXL345 Library
add_subdirectory(ADXL345)
set(ENV{EXTRA_LIBS} "$ENV{EXTRA_LIBS};ADXL345")

#Add LIGHT Library
add_subdirectory(Light)
set(ENV{EXTRA_LIBS} "$ENV{EXTRA_LIBS};LIGHT")

#Add SYSTICK Library
add_subdirectory(SysTick)
set(ENV{EXTRA_LIBS} "$ENV{EXTRA_LIBS};SYSTICK")

#Add FreeRTOS Kernel Library
#git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
#Define properly the CMakeLists.txt file for the library to properly work
set(FREERTOS_CONFIG_FILE_DIRECTORY "${PROJECT_SOURCE_DIR}/src" CACHE STRING "Absolute path to the directory with FreeRTOSConfig.h")
set(FREERTOS_HEAP "4" CACHE STRING "FreeRTOS heap model number. 1 .. 5. Or absolute path to custom heap source file")
set(FREERTOS_PORT "GCC_ARM_CM3" CACHE STRING "FreeRTOS port name")
configure_file(${PROJECT_SOURCE_DIR}/src/FreeRTOSConfig.h.in ${PROJECT_SOURCE_DIR}/src/FreeRTOSConfig.h)
add_subdirectory(FreeRTOS-Kernel)
set(ENV{EXTRA_LIBS} "$ENV{EXTRA_LIBS};freertos_kernel")