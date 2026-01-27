####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/befeher/.silabs/slt/installs/conan/p/simpl7b951c1d2922b/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.12.0")
set(PKG_PATH "/Users/befeher/.silabs/slt/installs")

add_library(slc OBJECT
    "../${COPIED_SDK_PATH}/boards/hardware/board/src/sl_board_control_gpio.c"
    "../${COPIED_SDK_PATH}/boards/hardware/board/src/sl_board_init.c"
    "../${COPIED_SDK_PATH}/cmsis/RTOS2/Source/os_systick.c"
    "../${COPIED_SDK_PATH}/cmsis_common/platform/common/src/sl_cmsis_os2_common.c"
    "../${COPIED_SDK_PATH}/cmsis_common/platform/common/src/sli_cmsis_os2_ext_task_register.c"
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.c"
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.c"
    "../${COPIED_SDK_PATH}/freertos/cmsis/Source/cmsis_os2.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/croutine.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/event_groups.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/list.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/portable/MemMang/heap_3.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/queue.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/stream_buffer.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/tasks.c"
    "../${COPIED_SDK_PATH}/freertos/kernel/timers.c"
    "../${COPIED_SDK_PATH}/platform_common/platform/common/src/sl_assert.c"
    "../${COPIED_SDK_PATH}/platform_common/platform/common/src/sl_slist.c"
    "../${COPIED_SDK_PATH}/platform_common/platform/common/src/sl_syscalls.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/common/src/sl_core_cortexm.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/driver/gpio/src/sl_gpio.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emdrv/dmadrv/src/dmadrv.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_burtc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_cmu.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_emu.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_gpio.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_ldma.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_msc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_prs.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_rmu.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_system.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/src/em_timer.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_gpio.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_iadc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_prs.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_syscfg.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_sysrtc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_sysrtc_subsystem.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_system.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/src/sl_hal_timer.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/src/sl_clock_manager.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/src/sl_clock_manager_init.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_init/src/sl_device_init_dcdc_s2.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_init/src/sl_device_init_emu_s2.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg24.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/dma/sl_device_dma_s2.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/src/sl_device_clock.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/src/sl_device_dma.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/src/sl_device_gpio.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/src/sl_device_peripheral.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/iostream/src/sl_iostream.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/iostream/src/sl_iostream_rtt.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_cpp.cpp"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_dynamic_reservation.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_pool.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_pool_common.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_region.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sl_memory_manager_retarget.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src/sli_memory_manager_common.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/src/rtos/main_retarget.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/src/sl_main_init.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/src/sl_main_init_memory.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/src/sl_main_kernel.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/src/sl_sleeptimer.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/udelay/src/sl_udelay.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/udelay/src/sl_udelay_armv6m_gcc.S"
    "../${COPIED_SDK_PATH}/segger/systemview/SEGGER/SEGGER_RTT.c"
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
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/MGM24/Include"
    "../${COPIED_SDK_PATH}/platform_common/platform/common/inc"
    "../${COPIED_SDK_PATH}/boards/hardware/board/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/clock_manager/src"
    "../${COPIED_SDK_PATH}/cmsis_common/platform/common/inc"
    "../${COPIED_SDK_PATH}/cmsis/Core/Include"
    "../${COPIED_SDK_PATH}/cmsis/RTOS2/Include"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_init/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/emdrv/dmadrv/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/emdrv/dmadrv/inc/s2_signals"
    "../${COPIED_SDK_PATH}/platform_core/platform/emdrv/common/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/emlib/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/common/errno_error_codes/inc"
    "../${COPIED_SDK_PATH}/freertos/kernel/include"
    "../${COPIED_SDK_PATH}/freertos/cmsis/Include"
    "../${COPIED_SDK_PATH}/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure"
    "../${COPIED_SDK_PATH}/platform_core/platform/driver/gpio/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/peripheral/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/interrupt_manager/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/interrupt_manager/src"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/interrupt_manager/inc/arm"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/iostream/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/memory_manager/src"
    "../${COPIED_SDK_PATH}/segger/systemview/SEGGER"
    "../${COPIED_SDK_PATH}/platform_core/platform/common/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sl_main/src"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/inc"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/sleeptimer/src"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/udelay/inc"
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
    "SL_CODE_COMPONENT_MEMORY_MANAGER=memory_manager"
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
    $<$<COMPILE_LANGUAGE:C>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:C>:-fno-lto>
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
    $<$<COMPILE_LANGUAGE:CXX>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-lto>
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