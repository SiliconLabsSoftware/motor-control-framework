add_library(simple_foc_platform_specific STATIC
    driver/efr32_mcu.cpp
    driver/efr32_pwm.cpp
    current_sense/efr32_mcu.cpp
)

target_include_directories(simple_foc_platform_specific PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/driver
    ${CMAKE_CURRENT_SOURCE_DIR}/current_sense
)

target_link_libraries(simple_foc_platform_specific PUBLIC slc)
