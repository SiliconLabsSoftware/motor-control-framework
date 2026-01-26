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

# BEGIN_SIMPLICITY_STUDIO_METADATA=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=END_SIMPLICITY_STUDIO_METADATA
