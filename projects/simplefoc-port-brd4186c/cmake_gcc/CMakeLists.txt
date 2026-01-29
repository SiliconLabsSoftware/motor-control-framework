# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	simplefoc-port-brd4186c
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# --- Arduino Layer ---
add_subdirectory(${CMAKE_SOURCE_DIR}/../../common/arduino_layer ${CMAKE_BINARY_DIR}/arduino_layer)

# --- simpleFoc platform specific ---
add_subdirectory(${CMAKE_SOURCE_DIR}/../../common/simple_foc_platform_specific ${CMAKE_BINARY_DIR}/simple_foc_platform_specific)

target_include_directories(simple_foc_platform_specific PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../common/arduino_layer/generic
    ${CMAKE_CURRENT_LIST_DIR}/../../common/arduino_layer/specific
)

# --- SimpleFOC static library ---

# Adjust this if your submodule is somewhere else
set(SIMPLEFOC_SRC_DIR ${CMAKE_SOURCE_DIR}/../../external/simplefoc/src)

file(GLOB_RECURSE SIMPLEFOC_SOURCES
    ${SIMPLEFOC_SRC_DIR}/*.cpp
)

# Add platform-specific strong implementations directly
# This ensures both weak and strong symbols are in the same compilation,
# allowing the linker to correctly choose strong over weak
list(APPEND SIMPLEFOC_SOURCES
    ${CMAKE_SOURCE_DIR}/../../common/simple_foc_platform_specific/driver/efr32_mcu.cpp
    ${CMAKE_SOURCE_DIR}/../../common/simple_foc_platform_specific/driver/efr32_pwm.cpp
    ${CMAKE_SOURCE_DIR}/../../common/simple_foc_platform_specific/current_sense/efr32_mcu.cpp
)

# Use OBJECT library to avoid static archive symbol resolution issues
add_library(SimpleFOC OBJECT ${SIMPLEFOC_SOURCES})

target_include_directories(SimpleFOC PUBLIC
    ${SIMPLEFOC_SRC_DIR}
)

# Include the definition of the slc_simplefoc-port-brd4186c target,
# which contains the content of the SLC project
include(simplefoc-port-brd4186c.cmake)

# Provide arduino_layer include paths to slc for compilation
target_include_directories(slc PUBLIC
    ${CMAKE_SOURCE_DIR}/../../common/arduino_layer/generic
    ${CMAKE_SOURCE_DIR}/../../common/arduino_layer/specific
)

# Link SimpleFOC to slc so it inherits SLC headers (sl_gpio.h, etc.)
target_link_libraries(SimpleFOC PUBLIC slc simple_foc_platform_specific)

add_executable(simplefoc-port-brd4186c
    # Add additional sources here
    ${CMAKE_CURRENT_LIST_DIR}/../motor_control.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../example/open_loop_velocity_6pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../example/hall_sensor_velocity_6pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../example/torque_velocity_6pwm.cpp
)

target_include_directories(simplefoc-port-brd4186c PUBLIC
    # Add additional include paths here
)

target_compile_definitions(simplefoc-port-brd4186c PUBLIC
    # Add additional macros here
)

target_compile_options(simplefoc-port-brd4186c PUBLIC
    # Set additional compiler flags here
)

target_link_options(simplefoc-port-brd4186c PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(simplefoc-port-brd4186c PRIVATE
    slc
    SimpleFOC
    arduino_layer
)

# Include managed project content if available
include(simplefoc-port-brd4186c_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(simplefoc-port-brd4186c PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET simplefoc-port-brd4186c
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_SREC_CMD} "$<TARGET_FILE:simplefoc-port-brd4186c>" "$<TARGET_FILE_DIR:simplefoc-port-brd4186c>/$<TARGET_FILE_BASE_NAME:simplefoc-port-brd4186c>.s37"
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_IHEX_CMD} "$<TARGET_FILE:simplefoc-port-brd4186c>" "$<TARGET_FILE_DIR:simplefoc-port-brd4186c>/$<TARGET_FILE_BASE_NAME:simplefoc-port-brd4186c>.hex"
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_BIN_CMD}  "$<TARGET_FILE:simplefoc-port-brd4186c>" "$<TARGET_FILE_DIR:simplefoc-port-brd4186c>/$<TARGET_FILE_BASE_NAME:simplefoc-port-brd4186c>.bin"
    COMMAND ${CMAKE_SIZE_UTIL} "$<TARGET_FILE:simplefoc-port-brd4186c>"
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET simplefoc-port-brd4186c
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()
