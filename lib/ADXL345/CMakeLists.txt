add_library(ADXL345 STATIC adxl345.cxx)
target_include_directories(ADXL345 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ADXL345 PRIVATE libopencm3)
target_link_libraries(ADXL345 PUBLIC freertos_kernel)
