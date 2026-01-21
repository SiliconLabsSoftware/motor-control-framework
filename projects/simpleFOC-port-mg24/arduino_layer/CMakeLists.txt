add_library(arduino_layer STATIC
    # Generic Arduino implementation
    generic/Interrupt.cpp
    generic/Serial.cpp
    generic/adc.cpp
    generic/pinToIndex.cpp
    generic/wiring.cpp
    generic/wiring_analog.cpp
    generic/wiring_digital.cpp

    # API
    generic/api/Print.cpp
    generic/api/Stream.cpp
    generic/api/String_ex.cpp

    # Specific configuration
    specific/arduino_serial_config.cpp
    specific/arduino_variant.cpp

    arduino_layer_init.cpp
)

target_include_directories(arduino_layer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/generic
    ${CMAKE_CURRENT_SOURCE_DIR}/generic/api
    ${CMAKE_CURRENT_SOURCE_DIR}/specific
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(arduino_layer PUBLIC slc)
