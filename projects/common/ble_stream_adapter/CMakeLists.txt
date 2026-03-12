add_library(ble_stream_adapter STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ble_stream_adapter.cpp
)

target_include_directories(ble_stream_adapter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ble_stream_adapter PUBLIC slc)
