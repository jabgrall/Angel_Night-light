add_library(LIGHT STATIC Light.cxx)
target_include_directories(LIGHT INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LIGHT libopencm3)