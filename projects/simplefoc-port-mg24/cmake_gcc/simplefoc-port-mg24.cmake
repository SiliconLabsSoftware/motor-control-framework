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
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:simplefoc-port-mg24>/simplefoc-port-mg24.map"
    "SHELL:-Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r"
    -Wl,--wrap=main
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA