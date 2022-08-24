# add the executable
add_executable(AngelNightLight.elf Ange.cxx)
target_include_directories(AngelNightLight.elf PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(AngelNightLight.elf PRIVATE $ENV{EXTRA_LIBS})