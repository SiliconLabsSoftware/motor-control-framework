####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/befeher/.silabs/slt/installs/conan/p/simpleb526998f4a4d/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.6.2")
set(PKG_PATH "/Users/befeher/.silabs/slt/installs")

add_library(slc OBJECT
    "../${COPIED_SDK_PATH}/hardware/board/src/sl_board_control_gpio.c"
    "../${COPIED_SDK_PATH}/hardware/board/src/sl_board_init.c"
    "../${COPIED_SDK_PATH}/platform/CMSIS/RTOS2/Source/os_systick.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_assert.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_cmsis_os2_common.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_core_cortexm.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_slist.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_syscalls.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sli_cmsis_os2_ext_task_register.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.c"
    "../${COPIED_SDK_PATH}/platform/driver/gpio/src/sl_gpio.c"
    "../${COPIED_SDK_PATH}/platform/emdrv/dmadrv/src/dmadrv.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_burtc.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_cmu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_emu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_gpio.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_ldma.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_msc.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_prs.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_rmu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_system.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_timer.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_gpio.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_iadc.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_prs.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_sysrtc.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_system.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_timer.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_init.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_dcdc_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_emu_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/src/sl_device_clock.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/src/sl_device_gpio.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/src/sl_device_peripheral.c"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c"
    "../${COPIED_SDK_PATH}/platform/service/iostream/src/sl_iostream.c"
    "../${COPIED_SDK_PATH}/platform/service/iostream/src/sl_iostream_rtt.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_cpp.cpp"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_pool.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_pool_common.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_region.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_retarget.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sli_memory_manager_common.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/rtos/main_retarget.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_init.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_init_memory.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_kernel.c"
    "../${COPIED_SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer.c"
    "../${COPIED_SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c"
    "../${COPIED_SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c"
    "../${COPIED_SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c"
    "../${COPIED_SDK_PATH}/platform/service/udelay/src/sl_udelay.c"
    "../${COPIED_SDK_PATH}/platform/service/udelay/src/sl_udelay_armv6m_gcc.S"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/cmsis/Source/cmsis_os2.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/croutine.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/event_groups.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/list.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/portable/MemMang/heap_3.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/queue.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/stream_buffer.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/tasks.c"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/timers.c"
    "../${COPIED_SDK_PATH}/util/third_party/segger/systemview/SEGGER/SEGGER_RTT.c"
    "../app.cpp"
    "../autogen/sl_board_default_init.c"
    "../autogen/sl_event_handler.c"
    "../autogen/sl_iostream_handles.c"
    "../main.c"
)

target_include_directories(slc PUBLIC
   "../config"
   "../autogen"
   "../."
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/MGM24/Include"
    "../${COPIED_SDK_PATH}/platform/common/inc"
    "../${COPIED_SDK_PATH}/hardware/board/inc"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src"
    "../${COPIED_SDK_PATH}/platform/CMSIS/Core/Include"
    "../${COPIED_SDK_PATH}/platform/CMSIS/RTOS2/Include"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/device_init/inc"
    "../${COPIED_SDK_PATH}/platform/emdrv/dmadrv/inc"
    "../${COPIED_SDK_PATH}/platform/emdrv/dmadrv/inc/s2_signals"
    "../${COPIED_SDK_PATH}/platform/emdrv/common/inc"
    "../${COPIED_SDK_PATH}/platform/emlib/inc"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/include"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/cmsis/Include"
    "../${COPIED_SDK_PATH}/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure"
    "../${COPIED_SDK_PATH}/platform/driver/gpio/inc"
    "../${COPIED_SDK_PATH}/platform/peripheral/inc"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/src"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/inc/arm"
    "../${COPIED_SDK_PATH}/platform/service/iostream/inc"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src"
    "../${COPIED_SDK_PATH}/util/third_party/segger/systemview/SEGGER"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/inc"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src"
    "../${COPIED_SDK_PATH}/platform/service/sleeptimer/inc"
    "../${COPIED_SDK_PATH}/platform/service/udelay/inc"
)

target_compile_definitions(slc PUBLIC
    "DEBUG_EFM=1"
    "MGM240PB32VNA=1"
    "SL_CODE_COMPONENT_SYSTEM=system"
    "HARDWARE_BOARD_DEFAULT_RF_BAND_2400=1"
    "HARDWARE_BOARD_SUPPORTS_1_RF_BAND=1"
    "HARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1"
    "SL_BOARD_NAME=\"BRD2704A\""
    "SL_BOARD_REV=\"A00\""
    "SL_CODE_COMPONENT_CLOCK_MANAGER=clock_manager"
    "configNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2"
    "SL_COMPONENT_CATALOG_PRESENT=1"
    "SL_CODE_COMPONENT_DEVICE_PERIPHERAL=device_peripheral"
    "SL_CODE_COMPONENT_DMADRV=dmadrv"
    "SL_CODE_COMPONENT_FREERTOS_KERNEL=freertos_kernel"
    "SL_CODE_COMPONENT_GPIO=gpio"
    "SL_CODE_COMPONENT_HAL_COMMON=hal_common"
    "SL_CODE_COMPONENT_HAL_GPIO=hal_gpio"
    "SL_CODE_COMPONENT_HAL_SYSRTC=hal_sysrtc"
    "SL_CODE_COMPONENT_INTERRUPT_MANAGER=interrupt_manager"
    "CMSIS_NVIC_VIRTUAL=1"
    "CMSIS_NVIC_VIRTUAL_HEADER_FILE=\"cmsis_nvic_virtual.h\""
    "RTT_USE_ASM=0"
    "SEGGER_RTT_SECTION=\"SEGGER_RTT\""
    "SL_CODE_COMPONENT_CORE=core"
    "SL_CODE_COMPONENT_SLEEPTIMER=sleeptimer"
)

target_link_libraries(slc PUBLIC
    "-Wl,--start-group"
    "stdc++"
    "gcc"
    "c"
    "m"
    "nosys"
    "-Wl,--end-group"
)
target_compile_options(slc PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:C>:-mcmse>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>
    $<$<COMPILE_LANGUAGE:C>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:C>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:C>:-fomit-frame-pointer>
    $<$<COMPILE_LANGUAGE:C>:-g>
    $<$<COMPILE_LANGUAGE:C>:-fno-lto>
    $<$<COMPILE_LANGUAGE:C>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:CXX>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:CXX>:-mthumb>
    $<$<COMPILE_LANGUAGE:CXX>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:CXX>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-mcmse>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Os>
    $<$<COMPILE_LANGUAGE:CXX>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>
    $<$<COMPILE_LANGUAGE:CXX>:-g>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-lto>
    $<$<COMPILE_LANGUAGE:CXX>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:ASM>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:ASM>:-mthumb>
    $<$<COMPILE_LANGUAGE:ASM>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:ASM>:-mfloat-abi=hard>
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-x assembler-with-cpp>"
)

set(post_build_command )
set_property(TARGET slc PROPERTY C_STANDARD 17)
set_property(TARGET slc PROPERTY CXX_STANDARD 17)
set_property(TARGET slc PROPERTY CXX_EXTENSIONS OFF)

target_link_options(slc INTERFACE
    -mcpu=cortex-m33
    -mthumb
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -T${CMAKE_CURRENT_LIST_DIR}/../autogen/linkerfile.ld
    --specs=nano.specs
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:simpleFOC-port-mg24>/simpleFOC-port-mg24.map"
    "SHELL:-Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r"
    -Wl,--wrap=main
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA