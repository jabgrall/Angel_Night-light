add_library(SYSTICK STATIC sysTick.c)
target_include_directories(SYSTICK INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SYSTICK libopencm3)