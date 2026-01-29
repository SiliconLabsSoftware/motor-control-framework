####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/befeher/.silabs/slt/installs/conan/p/simpl7b951c1d2922b/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.12.0")
set(PKG_PATH "/Users/befeher/.silabs/slt/installs")

add_library(slc OBJECT
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
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:simplefoc-port-brd4186c>/simplefoc-port-brd4186c.map"
    "SHELL:-Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r"
    -Wl,--wrap=main
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA