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
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32ZG28/Source/startup_efr32zg28.c"
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32ZG28/Source/system_efr32zg28.c"
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
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/clocks/sl_device_clock_efr32xg28.c"
    "../${COPIED_SDK_PATH}/platform_core/platform/service/device_manager/devices/sl_device_peripheral_hal_efr32xg28.c"
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
    "../${COPIED_SDK_PATH}/devices/platform/Device/SiliconLabs/EFR32ZG28/Include"
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
    "EFR32ZG28B322F1024IM68=1"
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
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:simplefoc-port-brd4401c>/simplefoc-port-brd4401c.map"
    "SHELL:-Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r"
    -Wl,--wrap=main
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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=END_SIMPLICITY_STUDIO_METADATA