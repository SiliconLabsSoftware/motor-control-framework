####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/befeher/.silabs/slt/installs/conan/p/simpl7b951c1d2922b/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.12.0")
set(PKG_PATH "/Users/befeher/.silabs/slt/installs")

add_library(slc OBJECT
    "../${COPIED_SDK_PATH}/boards/hardware/board/src/sl_board_control_stub.c"
    "../${COPIED_SDK_PATH}/boards/hardware/board/src/sl_board_init.c"
    "../${COPIED_SDK_PATH}/cmsis/RTOS2/Source/os_systick.c"
    "../${COPIED_SDK_PATH}/cmsis_common/platform/common/src/sl_cmsis_os2_common.c"
    "../${COPIED_SDK_PATH}/cmsis_common/platform/common/src/sli_cmsis_os2_ext_task_register.c"
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32MG24/Source/startup_efr32mg24.c"
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32MG24/Source/system_efr32mg24.c"
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
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32MG24/Include"
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
    "EFR32MG24B210F1536IM48=1"
    "SL_CODE_COMPONENT_SYSTEM=system"
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

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA