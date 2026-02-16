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
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:simplefoc-port-thingplusmatter>/simplefoc-port-thingplusmatter.map"
    "SHELL:-Wl,--wrap=_free_r -Wl,--wrap=_malloc_r -Wl,--wrap=_calloc_r -Wl,--wrap=_realloc_r"
    -Wl,--wrap=main
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=eJztfQtz3DiS5l/pUGxc7N60qvh++LpnwiOrPd61Wg5Jnr3Z9QaDYkElrskih2TJ8kzMfz+Ar+KbAAiwyN6bnna7qsjMLxNAIgEkMv9+cf/h5tPHD1cfHv5i3T98fvfh1vr07ub+4s3FT3949b0vX354AVHsBoefv1yIG+HLBfwGHJxg5x728KvPD79cGl8u/vD7L1++HH4Ko+C/gZPARw62D+DPR2fjB7ujBzYxSI7h5uhcBYcnd7+JXT/0wFPgXIZBlFwmz5Bc6B1j304SEG32jpNyggRDECXf7x34X0ivYHCR8oMPwP//9BR4OxCdmDopi9ozxZOuB07PxZ7leIHz1fLtg70HkRXEjut5dhJEVkZj85yi2IMDiOwE7OBLSXQE6Zeee/iafvNkezH8akvMLokA4MTIt92DFSd2lFiJHX/lxOUxsKMdop1EgcdLZUHES0k78OI6wHIPbmLtnJ0zAxvgH3m1OPCD6HvZtyKwh2N2Hl4cmPwCh8bdw+39FXvS99fv31/fWXcPDxaizlo3sQdAmLg+H73sfHsXvUyk/NM2s5jVr9yD4x134JOdPMOPx8hF0iTHnRu82eZGd1vY1YzWT8X36acf+MwWDwBOE1A2rvOFfUwCqESsCSMzeTvwZB+9JB3Tm4zz49H1EvdQbYN2w4y2793DNeyVfhgcwCGJ8wZmQzq1pTlly7ET2wv2rBmAF0T82T7sPNgoXImz1Dok7gYxnI5tP6fPXPUt+rzwp9OMe4Bz/8FhLEZqUyL03cbb0dGlNT3lEJ3N9uQP3IDE3sHBsgwDBB/a5BxcEP/Wm6A0V/fpR54tkNJ2HTf5bsW7r5YkSOpGlJAEHU3SeDfz7+KOR3teQDPaUxD5vW/0vPcuZTTyVs+79y4ULzh8tB/7gWKQuXl/IykEBPrQBMcIU5IuanXjh1Y5x9Dy976k5Ga16f20OjVs5G3ebtuiObaZfrcVVW1TebcZ3G2LU9ti0uD/HifAnwN+gxEp+g7DQdX4HzJjw6b1U2mE8FGWXg52PtsxVl+Od9tixaT5YYtkUPiCr7FhAjxVh2U7fjiD2ks+LKGX7hFf5BkbhsAfj5HtzwG9ZMQWfOLMBD5jxBC84x/ngJ6zYQgcbW/NgbzgwxI65Hx4CmZBf2LFUgDfhpRjJ3LDJIhmkaPFkaU4oefNIkTOhyF0MM/wBcyHLzjG0PWcBXvJiSH8pzhyZhnAJSOG4PehE81iO0tGTMG7syi+4MMYuoVW+nPhL5kxFOL5aaaeXzJiCv51JuyvrKG70ixDNmfDErg9j6NW8GEJ3bGdZ87L2CYnhvC/gu+xYx/mwF9hxVAAD7p9c6Av+DCG/vpoz+IcV3lxEAGdDbqHebYWuniyFAmk59izSHJixVKAuWZfj8Ps6800+3rsZ1/fdr3H4HUO9BVWLAUI7efHmTbZqrxYihDP4kfkbBgCD53DLC5/wYcl9GgWs5+zYQvcit39AYKdSYAqO4aCxE5kJ85zaO/mkKPOjaUYYEYTWmPGUoh5dtti5rttMfTOn/azYC85sYU/0xHLiRND+LP5nDw8zuNsLueRh8852zYzj13ml509S68v+DCE/m0XzGJvCj7sA1e4gm9y4h65QvAC1qMjD/X+3P9DX0wZivH1g65QwpEXSYPRRvgMvuseHKIgtGawq50Evks01hvqOfW9/DNEtK0Rxu9iHTHiLpENxcSWU50CzAl2wHI8O47dJ9exEzcg2u7EBNrDZQJwdx7kvWym6BwcjkTbCJhKLshOgQbFBGTTPe4wKglP662IJpcOWhCeCC90PTJXFR9gSXoKRNilYx7tW9KdBC6xkyPRdgMuupIwDjySqb4VNR5NnMeycUIQ9DumAohoWyM8qYXQKZXnxRwAVklP7+Ec8BV0mXUh/i5gejWN4BrCM3z8mx2NBWJ386Fz/KYOmOz2XeXWHVabZ4rZFvJmn4uWrpOc5PbVbkOnETFsQTZJ8zZvU930GmoSQ9+ti8IPblKd3mZp67PFV5Bckf2omMYBo8BsAQlnKPrrTLVEClMuNJFZpL5uVM/rQGqfaoo/zUi5grY14oVF6OZIvDHSsdJqEbaebaLRSyHOENvJMvXQtmJp/kaqMGYs16yycOlr83czTj3sHJ2Lpl+Rb4tO8xAIrCevflAssDs5sh6RcwrBBL87qwAd3Lj03SkucJ67ZzGORo4nVRxDA1MXs7AwTWbTx0dOEQWQzgQ+Z8UMOumybgp2knUeFvgQRG74DCI47c0kQp3j+qam2hBgZw4bOssNepMZ0/E2E3jK2PDh8TYTdtpLTP0p38huoUzBTnkTBcdUzCRBnSMHQazke0gWl89GnBPfOe1fakVIcr3gmEALPEWy9Lony1RCpsYMeNMe1jnPqUho0dhpEd3MZro0bCgP0t92cZtVYVl8DzulVYYSWubO0AeLECU8DEtdtaB17WKWLKcsqzz6P6LecD2bDNnN6kUi1zkFOfFbrRNdNgj7KTjVWsMhqnJj3vbziUCcTGImG+MeEhBFxzBhsTlC18+aWRRHz6Awm9vxYze2DrANrBc3So5MfeCW3tJGt1EEQifb2bK0tTKKNoFyV0If0zktHpM5z51ZecXpxkTtYfcEBCwBrz7D6a9PqGHmy7OKeRre87tdBRKWbZSTLJumwoJBLysyGEcJy9PzPtAFm/W5U6XaGZqUQkmFGa6wYHCqxB+xyxZyvZfw13PBZnH2rF7p4fxWrY6HoZmoEy6MRZvd9K7VKJ6x+w5/gi5fBBCU7MrBvGL1QWAw8FuFQtLAe87iDbBl3noRSOxoD1hOWFhNVuXLvJ0YGjysBmJjspuNHoYb+O+8zVIyZS5OGATeTONnhDUX0c4hEyeDsD+DBT9xXZ87O5ftyV2uGUxP3hrzSlLhyn7ihtMNOCR5QTHSaH4a4fAQLM5dzivvze8nN4hESUB+/tbZGdJCghy8nFxTqT1DaLctRmfb+EyRMI7hr4rbZMHA/iByX0F0ACwn0i7MJyYsjEyFIjt7Uofd4sJI2+nZTGajZugmFU6s9F4ly1n5DVYrdFHK4cpeU8VkXmXB1iLwxcx1ZPFXN+9+Oc2bKEqJnn/j7YSFqbkriJ7uXVfZTO9RlWqs6Q2ZLGHZPBI0ODIXJitwM6MsJUPmoszZseoMGUynddJMbVZDii5e65tNK2Oci67KJCVVNkzbmSfuJp/FzUrHHfDs7+efkTIcDI1GRrAwGCfy061dRsuyI/9F862942zuuaJucFqficiVz26Y5VrKTcOJ/PlGF95DTfUCfxe90KVMyErHn3ncZiAYDNpUEduMXNr5T5SX392bepWKbNhs9uwyVdAk9MZRdjqGSsTbNrPzbNzl7c9B2BPlxc3FBEk4mXbgmuYByprITPGVXG4l4fVZac99PEOGLOAzWxSmIqSGtUqUOtUSJIKKmjLGlZOcggqwRwWmo2J0y7wGi/w2eRuXx+bmfg2XR3xFv40LVSFhDCsnOQUVqtPBGFVOcgqqiH2Pj6b3+CzFN2tgJ6pTsLHanapBI9qBOlsWv9L4s5jekfTpvO7TFOfunlEY4yKuvN2JKk3ga7M4LWqCq1CelE+bg/bqZKdocFJe6l7tMUhKnXZcNguq2lggTQ7Q7nNTUmX397fpebLR5GD7T8cDcwtSITsF3QuIYjbBWjV0FbLT2jVis7KqtWpEuqjqxGXtwQFE1GUYBvFVaU/17hnDI7+P2+3dM4ZFnrumx7tnjIu8WGy3d88YFnHZwk5UnOb5OuWpKxDG4IiLD3avQFjPBtNHJXnVNxxgNBXeeldH7LHlVKdj4zUbtKlPX8kxhkh0VMtx13FKRSYQRYfAgn8G6LrUjih7D5c95SYeBo2W7yy3SGft2MVwcfv9U+snpL4Vu8v79ZoZTeKL3tjI8bLrVmXpHnzvmqMt2EXuC2bYYOtd5EqeP7yD0RZ4pogtolb0U4qN8IWERTBaOFR1kndbiuXDIk7aTmnZzlOJMAuLZDE7nSQp2qRCe0qJE0SGUcfpxjh56ZnTcW0mqcG6QRbEp4Jks6Lqxjh1aXUik5YH5Ar0xGEqXGbrrm6sDBZgJ0psTkJ6gU49E6lRYrc5MYSXzYFElWB8fGS23B1EXmNEDb6SGJRXB+lkwQ4wt44yxIlBZ+HcRaZ2jBolhtsjQ4CZ7JPkFFntlXTjZb9pUsjCeMlcejjT1yIVTeRLkSpxJu4TL5AFcRbuEy+MU2Nj6g4DL5Qn8oz8EY5Ap0b99c23fCHXGTGaaDhCZgSUVZRSN0724Ur8C1pmCXVHtsWZ1bOcsv0+eV83lTSIJYoUUVUt9W7tdtCfFH90IgheEyux469p/ho4Foi6MAb2UV6L36Zu6p7AJRvUT7Fj3UGfW9uyxT7Ka23GCt9KXQXkhbs/HBzvuBt7rbNdy8YI4dfkzbhFcLc5/22bGFY7dSGiCN/qBUQYs9XAk/wtzUwFu+FEMHVC1JpBdz9ZaCWnQ4MjPQ/0ZXkqjiodChx+eEwvxBoTcdToDOOgNRc9A/fu4fZemn20Q6tKrrEUaqML5YQomi6IoeNJVnmvC0aFzKR269H0fXCMsAuZN+VDCwCXrJhnVcSM97ZOiE/nxJ/LniIABlPQtd7IsgiRdnGXvovbSeCTbccVQm0zrNuc+fZEicZGRsExcQ9EcQh9QKq0KKDsQBgBx07AztqBJ5QbCU6GRGdIfcD6KVPABC/gkFh7KGvIBFyTHgWkXyBpNBpZwKnSooDiQdeXBYyCDs10C+LY3gPr8fj0ROYq9oFpU6T0AsIoSALiKpC9sFoUKWGhLUHb86zD0X8EZOfLQ9g6yFIC/BbZYcgQWZUeBaQwiBL70WNiNKu0aKBEwX9Dm8ZEM1VaFFD+egRHJiopCVGAiIEfPjMZ9CdKNDASOy0sD6dEJk3TpEcB6R6RuGGGqEGOSkdp5RF2ZrpFkGYVbcdE3n4floIODQS0082kjU6UeKw6CstFt+N8A/wb+7Cn35l8BnZoySTLlqaaCgG2OZbtiSTvPdn3V1dTIlzf3t1YVzeybP368B/T0/8cgoMVA+c4uqGH2TJIr0zaBWppWxV1e0K6LZiQJvvpRWzHRIds1KBzPkxwV30Z60Wy5pChhyezdkgnuSnWD7slSk5M+9AcyHM+bHVOfrozTfM0pz25BMTh8OeJFe/eaZkwQKs0Rqb0gU2LCQCadIhApGv6CcyL94mYZouJCVxLAkRs677oBPYtQkQwkBs6qcFLAmRsM8dzCt+SQh9j0jOM4fPNnpfod9ZPJw80Wsh22PO99RopHp78hJOaAjHpYU1D0uKgpEmOYvlUkvDTGlsMMZUEz328EYP9UDHM9vNpjNeLC74R9//r9++v72g6RvamdffwQDIAMsm2J8DbjM62To5m+yMlQNIdRrDQbsOcBGGHpSBHswvjodqv+fxiuYcdeGUCrIfubEOn66vGCRxOgUb0ypvt5xhORttH8ASekbCuZz/G23fg5X67Ay/xZez6oQeeAucSObfpPipwknhb//4yeXYP+9A7xr6dJJCO3VWssQPkSHPwhvg8CBB6JzsfbPzd+UBWIAwARRVXclOUXlJAx4HIVYmOoBN6jVS+o/bJTp5nEQmDfTEKc5IZRddxk+8WHJiWJEjqRpQ2AsLhOiA+hbC9S7/Y3rvw8eDwEQG+eX8jKdvSD2DHvBLj2xdHx5LdY2BHu3j7DP/8ZsPFZvqZNZOeuOUi1bvjBelefVlO8Gy806hedrzHAiKZ86qFP7GnXovRmbGRsgF5ph6SM0dBEDNxbuYzPwPLbTXD/Uzc+YyLsXxAM/AaSmPDkn3PqRYXFrUVH08hcLZIZ2jDRgaOGTjWb2HOaPDcA3SoomOYnMngtvkznpZp5N/a6H7RfBiCbBtzZtW3KzufjznjRu9bd89n/+fVZqV85hm4zjti6yXZzsN4XolP1bEaTNODwndlzO5pNf/u+o+f31vXv9zgvpCucIVPf5SlP//6Fvel+4/W1e27a/jHzafbX69/fbDu/3L/cH2Tbhi82N7xtLuKS/JPb+/e/fvbu2vrj7fwb9a761/efv74YN39Yv3x7a/vLIhRoCR1//nTp9u7h3tLLKhNJUQDCqoso/Lr25vrmp7+11+PQfJ//nj3TtIF5W32iZjq3fWfO4i+FQRieo2Gvfp4e/Vv1s3bX9+mVrTCoramxmXgBIcnd//r5xvr/t2/WQ9/urt++86CLN5+tO4fbu8gE+vT7YdfH67v7mvMJCIJSvBvH95+vH1vfbq7voef6bXw7vrPH64gtOu7D5/+dH339mMNXL52rOY8o2Z08/bdXb0pi/pwtCR/ubu+Rkt669+u7369riMvz3CKex60TN5/+nBbo5wlK6Ql96e3aTPe3P5aI4ouvBfXuaeQbqEt8n1MIwuN4N3DVYtwlv2AnnQ6HO4+f3roHIYtPxaX0dXN/Yd761fYsa0/f7h7+Iw6Ne2b1p/gOL6+s3758LHLuGU7ZAc4SqwXN0qOqELuVMN0c31ze/eXTpXUXUxcFncPD9bn+2vr7X19HsM38eWZk3V/ffXwodF5M4FPD022zLd3dV07QWuNTDKDf7y+/vTw4aahy2qt8xppz32M7Oj7L43wjp3zu9/hPLl3miOi8zGsh5pORudDhwCOw8aDSRB4t2GuGfThQ3r0UX67OTob9Ml5ht5uqpYg/X7osY0THpvNkoDXS1+W5+D+1OD+FL6ol3HzMI0Pay+wE8t+dBsWMGoeQOFwL26hDzMv76pnO0TphluNe3aMRcw9PfQa4Z09k//n3oFzf1Jj/U+F928fk2APDtvsSXQ8tvFmUAmqwoK+RLtn6cU+FoohxLCzE/uc/A/2IbAcCxoEJtxRqSL/cZR9+Rhr/gTdkjFnQr0HvptYTxG0vFYYpB7KORo/sMCrA8Kzdb4AhXq4Mzd8cYh/Y4fpBDi/3I4VJ/Zhl9r96jwoGjPwfn3t4f6734k6f/7f7OjgHvbxxva8M6i+ZA9ek8g+J4AQ7OxD4jp1Z6QjhIRrI0CXID2Ji88BAz3hu3+zU6I1n9r9G2cjwJo16bQPHo97ywMvoD4IduDJPnoJFgDf/gpSX8mO/A1KdpPY0R4kTQQ9j7W88EsffvMzoS8+EUPyfPQfGyjy7/gzby4ELn34zc/5cuByJ2qzgOhcEkAo6PtL+P3P2MuDFouTzR9Fc3q0b3K6hCvXn3FnqAH6edwkHhgU59g3X2WAsCctxpC6XJfLp0NwmX17FkA9vlwKq/rbfH2pcLWsvtUnNDo+5kzDUF8zwSLRVDEjW0236PLf02/mVRBfNFR6aftrl/+ef3cm3XBDRKKfXj/m8nbySCfVDE8sJDrp31O5fEK/XZ5+m1dBswEj0dbwLtjlU/H72bQ2O0Ci8Te8j3P5hB64TB+4LB+YeVjOD5FotPYshS73sw9PbkhI9NG3L3kJVyXAiX9Gv2/Sv86tH97IupfvPY/1HyvQnyZMRJTqZyHaKV3c7LPl22Ed1f/N6X354fLGDn/+p3++/fzw6fOD9e7D3b9s/+mfP93d/uv11QOKxfmXTfoyBuYsqmvj7sAmP9ppws0DQYKw7iD4e19ShPBRll4OlO5Tj3rcuCuHeUr0oxsnJeGTC+f9eHmJ0pT8bKHYDyvVUOVLHzrAgdP62un+OgLF9x0XGLFQ+On5ItHLaL3nJQENy73TN4tuT+1A0DrPQZz8D2seMk1BA7vJ7v6lwyZ2ZSkzvLtkk4Vn7B6PrrdLT5E3+8NxUw7xRzu/KFlRaIXc6dlN9gC0gk+eve9KZbBqhfMcD/BNtN67jL69woGx98EhmTQwKJobTrwEDZ4/XTT5/2/wMzd4bZ7yvBf/f5AlHH254oMwn3maHux0hXf2Kv7WvnTBsex97WwNGgAk5iZInkGEkiAxEHj0rc4sG0Nc8iTJlx447JPnn5vRhDPYVyIVV5//n6nk1hjrjfohH2Sv8ENJ7vKbmzxftjNdTLTAi4bLzyEkJee4kXP07GgHQnDYgYPznS5cYjkSHeBqZNdaoOMHO0zx3hiIcfIECZrmp+KOVfrph5/+8Op76NGsZBB8WNwI6cuQSrBzD3v41eeHXy6NLxd/yAgUS/kyUPjobPxgd4RDKgbJMdxcpRcOPmWPfYI6/mMKfDhTySaNb4ZEIfkQRMn3ewf+9+csMXm6c1BtjxBSTdVxn4Dw91Cm2ueZ5MyDM+5BkqTBM1MF3PKDyrwxOGI9Ojlapj2mmZAs3xXsMu/NRzexlwZBJP2J7RopgjZOhEpEo5tb6K8pStQ9YT8ph+OXrvRBHZP4SEaqej+/+PEi36mz7m5vHy7eXPz9y8Xd9ce3Dx/+fG1Vf/py8Qbi3Hy5+Ad85/7DzaePH64+PPzFun/4/O7DrXVz++7zx+t7SOA//45yM/nBC9jBd1Lj+OOXi1ya69f0Lic0oG/+879OX2f5Bstvs+ZNORbN/+bmJv3yB9h/DvGb/NufoQwXz0kSvtluv337VhhEaBu3cbwtugVI723AJ086/ZIrEH3p7tLP7KwSIhru/BqX36Pen99lRT0//iFMX8iwbP43+hM15ql9Col//+XipCioE0TxHz/+RpT821RvcQuzrGlzlQ3t55RX/lvlMhP6uf5jdiWxMAm1n2LPSpNLpbXyosDre6h2e9QKYsf1PDtJc6ZgPJ+gLYG+J9OydN2/VbL8WDtn5+A8B/xj32NoUwCZ0igvcdn3WO0+GuZTqFxmcOh7+HQtq/LEYsbN0cm71G9kvBRnbncP13A0+GFwQBtneaP0HMhVfinHRO5ipf0KHZvWn3EKypZjJ7YX7BsM4CNZnuln+7DLD16Hfm69XaQbyZ+I2wRaT/TTSMeGe0DBi0724IK63wPwUTIF8FvrgPDfTe4fuui3xag8Z3EDEhuF+vxm9F6kIv2xTDn64yll5o+1NJ8/ouh60vyLrfkyZzGFUmpdqMjkVcXrEzi6F59LO4VcxeYRZDfsqElMRSCvlkv1bqX+MOn71Qq5hO/WqtoSvlsvVTz+8kBxWNKXKyVdcV/tLJU6+jJF9fSJNEermlPTzwdKC/MUPWQ0hzGP0CfOkLsFfu46j6mDnHQtiIYTect2/JAb7dKdYk768RjZPkfiyajxpCXu+EdepNH6jhtt+NjhKeBG3rchizgN/gtGTQs1l9AbdTdoaQN+7QqOMVxw86L+BO0mt3bdh07ErU+mfhpH2lZaWo4Tg+cnjmp/fnrlRtuVuDWoa/MzYK5jO8+8ZmnrK0Aljkd9LlryHrSPPGm/PtrcjG5BP6u4zs8l8EC6O8iNPM/x6nEcr3Dt7j0Gr9zIh/bzI0dnzI+5mYTQOXAz72HEraND0kUOe14soCNmJ85zaO+4cQCc+2XMzx9D5eyf9hypc1x+cLWRR65GkqsX/LKzuen82y7g0FuybMNWyoId9XxrKj3iO4Y5dWa7JgX1KvQR4ti1+KYQwdj6w6jIiPV6RwFXkveadVdJ3s0Td5en4NgiN96/T2zn6w1KtDk6AfWRsJPAd0cHXN/bpfIo39+BMAIOCtzJnNI0VSi1LLUmoaSRVrSlfDcPBS4qw9JSCY/QswiSIPkejjvpQ1TQ9Gh7nnU4+o9g3A0aIlWUF6elURRZoX4/Cv4b9hBq/lnJYMqXoYsUPlO3Z4wGqeVPGqX1ksOURNAGPPW7WfFfwreL8tAk70ypeM+cT7rvxIswT9B5OXoutNOuzJc63sFZL48b4N/Yh/32GdihJZMquSwvTvJSqyg4yctlSW+il8p63ENvYVR7ROd/6KrFuE+PSwzLp8Ak9jgeUYBJCSWjshwPiuo+uU6aTIcZZZzuik8MK+AAkxyAsz8jUjGOc4RLK7GT4+iEgkfM5dG0+cF4PjAmjrKcWIwzIeLSypw7EgOAWzKw/S2BMrvrUhXRsdMIFcEKWZgtyqc5OoPiVdtDVHEOsTCo5RhxQpcwi1VuAWoDSmitupvZX1lRO1XxLCKzMTdEcRggVeZwaTWZ1+BE0SHEU1wvJaywBDxC9HqqkMGIZMAkk04+NhMlEc+JA5So7UaLjpXeFCJyTnrpYQQa4JCZYHdqdHCOJnHoYJzzYJJh2JswTnFwyES2j5LaMSHFpvXxjjAwKSWAxNUbocRyqGAdduAQwgyIHSWFnEYGlhPNUOWEMGWOygkhPAzIADZkJvkwFTqpZWJAB1kmBmRColVzL5mIjZLzYcuAUjbI6AjVa0FXPmKeglKSnTZDNKhDrxvVvKN3qrrpTZifuwniBFcREaSfHHvppdsGbKlOmul6STLrmzWSPPplTjk+Pk6aqXuJ8yE50QvoJj3FHahQzJfa5SCdbPoqBNNBypIg/azTTS8fToxJ0vsxQyQrnZ4xcdYkp8yhRens2n3xcvOr+iVl18dngHURj4KLy1GOYnOvxoBlS3QxyPrRaNDIdD44dxDZcOEnktvWHYce0ORSyDSRVSWvQjFkmikZ+HKg3y7qYpA3fyurxOSGH2GCUlKw4lG0e9recYVT1gHAUyRLr/vxyDQybkWQ3IldZVmCxg4vvr5d4YnuWbHWY73TpUpk0+O6GdDvN2KRn7DuwqKPcX1mCvlTp5qHi4UVLkbGqz7+sw7FtMfWGdBvE2GRn7BGwKJfafFpXNJKIdExTGqNbqNz0I5q9hxYoWQrzR+YM8qV1/ph4snuGEOXvWh5XppSdflnTmRReTy2pF3mkIu2LchObMoesqkmppGuZ74qVF3/dqJScFjkKbd4cHLbrBJwSPIEXzh5X8i45m3UUCHTVupkYTmVhDlcGe2+H2wfWuAIoNeyYKMZ5EuvV8zEpzi9n4Fd3vNn4VQU6GXPqznKeIyp1khm0kh5LsHSLqG8ggx2j/rI5jJwoJ6FxTIijDSeBtumpBn1nCrxmqr5kC1UzZ56rmqWhF1eXaRGnlEfKRJgngJji29Yk3a50C7DUUvSU5uyn3R+Jkt/sIDNZNLxBTYXLvpyG1wmNvVxBzz7e9E7s09sSOY6yUlO00IXyTTvnOanSfPuh6nHYJ/Ojekh0IsLvuWJg/P/jMk78jpKPzwmHw4JWhRQI3B1k98ngWZxB9IL+ovJullmjL1PP6YCrj3p5mKUS1EPYfnaPaWSPZUB2Lby+y+mDYiKJ8yg/f+6+PHCCUIX7H5xPRDn9QTKwgf5Yz+WRRs+2clzqkKiNN9B5O7dg+2Vb6ff5lGX8Avxx5Qg2kGAnyRB1SXJ1HUt7RxEYPCysJPhuRQF2VQNQTLNqYDaad7JoOiqpkuGKqrkQAaS2JNhEBVdQSg0gUIbQTOVPWFTSKIkaYohazI589ap5hQgiirpsiwp0jQcrVz8pG1hGJIA/8XuEDgp3MkwqJommoqoG6QQmrm/yaVXNVkyBcFsG4piHmny7nWZmKRQIYOv6YZmmJrWtiozoG+naCHUvSZI0BJpRrvncURfS7zTyJ1LatThNKOaoia1LckMAjTzChOCN00FjntTnbXr1LMeVTILk9osSZcUTVTOCb480ybuNajLqLKmnw98NTkyoWcFmQuiasxqL1vgy9hqUt2LsipKiiq2HY/Z4J+u9hB2et3UJQ3iPx/0SiwaoeJVWRZ1Xdbavs584EE1PzUZfsVQZFkzxLaDMh/8rvzXpN1f1wVZ0ATznHKcMmwTG05FgSNAEs5oOAHl4IXTLVwASrpyTuzV9IiEi0bdEAS4hj2j1a8mISc0nKauCeJ5+001yzlhz5FNXTF0RT3jlFWJeCTdh9E1RZTgIve84Kt52kkXiIahwGW6cUaTWU0ET9h5DFUXdEGUzjjvVjLNE3trgmiYUtcu3mzoT8G4ZOANzYQLFFM/y9KwlSufDDtErqmS1LFFOB/2ai5+wj0R1ZDhPKudccDWc/2T7oqoIjT4yhnd/ErCDtK9VcHQ4ERrduzkzYq+Uq2AcNiagqKr4rwbat34G9UQSHuRKYkS9NjO2Y1q5RZIe5JpCGixfk789NMu2uCRZF3Sz+i0efTzLnT14bxrnFP59dz/xA6/KcqCrJ7Rb2gUvSDcbpBFQxX0jsPC+fDH1MsVQZFk45xLxUrVDtIjOUFUUcc5I/aIzuDriqYKcMiecaHVrjpC6LhBg6mIonjGtUqrqglh/9FVVRBNVTtj52+WTSE0nZKsSoaqiGc0PTHtHhtcL8LFrmKccZ+nlkuG9FBL0QXVFJUz+s61vDWE8OGSxVAMUT2jBaL3NxFvTZEE4Ywuz3GCw6kLhijrunZG5dPvLqumYQiyJp1x3FaK+5C6aqpuQo/hjPayUjyI2NGHE64qmOZZlikd5YmI8Suaoam6zkD7ZOXayYGiPR0WtpGuSj35tr0oqIrATa9FDv0qXsodbjhtKroqzQO1cgGNDCd0q3TDYBJuM3J7gSznD/HqzlSgwWCxrUQhxkgGHtJBiYISVLhWXUyb1DMkEXYwUdY01eyIap1fGLq+Jcm6YQqCzGD9x6BvTehWqqJImqwsoSWm9Kg0aAcKwiJahEiQscRxpEtaU1cVVWIRejFZDNptBRMtbeW5e9RQbj2KPWW4tlVnmACxcwURnoqqIhRBZXEwN0UAeqdOlBVNVwWVfy/CTv9FOMWZqi7JIv9xjJv+izz6FM3SIotNBjIJMBPZkctjatClFWbrUXgZBknFMFGIkiILDFZn08So5TAkjTdRFUPTzdkGB0a+StK1hagbuiCb8/amwYSYxIfWpmzC5SiD86MRCSgysRF6TSI0tqouSwyOMqhkGUj1RhyUgnYyFFHjb3bJc7uR3gEQTVM1TJm/qaLOi0coEexhEjq65G+4yLM+kYaKSoZqiJrCv3HIU7eRzomybpqpNNxlGUk+RNyd4AwiiSzCdZlkNyJfcmuGqOv8uxBmliPSi7yKKbO4z4kJvic3GHFnNyVDlhUW13sogU9RuqipkqrKEsftgZ5aUITLNxldvzNZxKLjwAS0MCXJFFRB59eL+2pZkZo6VdMUQZH59dqeIlekp7sy7KGqzG+C7y9bRRwEoImSJvCb83qqY5JuaEq6IImqylujfeU3ia/5o+wS0G2dAW6rfB7pTqsuSrLO5OATR7W10q+kUDVDkhSD41FcT0lYUjMFl1+6aLAITcHqrdXyruQOvAgdMI5r3oGin6ShqgqKNBTNmdRar29JalcNydBU2WAQZoLXBSK6q0MoYZSg6xxPIMfq/pJ2WFGALrfKIloTBzD1xpio6qoi67AbzAN0wh69gDqBrom8nelWUWPiRYssaKKms0g+gwl0ihdwaZiiAKeBuWzrlEBcTVVETdE4brL110cmNViqLMMV93xKbVdeJB5gmi4rgq7ww7yLXMh+i4xAsTtDv8oSFHTqKLHIXIIBN98XmGC/JFlWDUM1+HXeseq2hBdXZEURDYFjdxitnksap2/COVeTOO7RYdSpJU5zJ8BOzDEEBqP6K+GBJlyIq6bC4iYxBeRJNk5VVZRSkeMx4GitWcJpRFRUWdNYhIETAa6ViiU9CUOpjNBN//kx0+4vqYKEMrlwjDPIFr9lJGCWKpX+cO5S1EUB9g2d3+SXIy5i5WhXbpeaZgiaySIhYHqAvr1CKIubCtmZOvJ+XY/25FaAuhQ1kcWBWi/CKYv0S9HUoG8myBIDK9CBMPlbGucPXmkPaTTV1BU2KeR6FYiy+1P54ZqqapJsMrD4XdjScezLMvXiG44MXWJxL7IDnR8e0+IIBi06EzqszANNUqvSa2V2KALOjmP3yXWyOll0e3CmjDaLZbbz5gB0lxl2UZdFOQ1Vn03t4HCkcwV1DaWfY30uMwR1yr68aIoQqiEyPkAc7tDUe96X0GgJssIi1xM+WPpp9FJT4SSlMQ5zHIKLykFQLm0vFVmQZUOfQ7m5y5d3XLrYEwNi1RTG8eFDaJH/b3teTHup0tAkQTE6Euj3AbYrpRiJV/0G9IMNgn0VxIzKNEMmgq7JBMuxCNg7H2z8HY3vIsuaYhAER6KgFcqIBV2RdIWq7EMaKZMmzLcSO/46qfAC6uOmKXVk1CStVDIFhYjMLpyFO7IUDcP4JQLg7uH2/moSc1EQZLhkahvSkZILdw/X1lVRY4k6BbokKbLIegttyIw/UgeHqYKpSdDS8L+4RFCwljT7sCgaIuzy/DZ4GBWqJU30pQimrDDJt0Mj13DhU9IwdcNUFOjoLiYQulZalLRhTFUS0O3qZTQM5RUIQ5RkzZghnpW4jjTxTS0FJYQ0OO6mTyzlTDx/wdlLQ5WcliMQpWk24fJWnuFqL0FFecJtbRFaLWi6Zp8gCevIk0ZZCtA5U2QWlaEIQvF7azsT79wrKJZJYJHJluIiRK0QM/EdCAPVAjP4zx3jpZhJVxaovAy6iXmWiwQTkIu6hM60VZ1fNGnuj4MoOgQW/DOtqLgDcRZc0vyWsswMXE1BZ53VCcbI9kX2TBBLU6Yy0ZAkAbqxBoMZYBB0sf3WBE2jaEkRBdNkEXaYHSig5azUOIuBEClXbIqmmoaks7ho0gUviK3EpUxhcAm9YkHUdZNFftwquLwoH8SGDqhdyhwXlxJsVDiTs6hN9hQBkM5mmVnaurn67CTwqYPHVE0wNEFhEfDWh8+JgmPiHujOoeGawRBUXWHRvH0AdyCMgIOoZiniXeTr0BlMyZRVSVFYrHD60IIXyMraQ6WGlEZdElG9PzhBceyUxZ4aXV4SA+WvNFncL+/D57kx5e0bWTd1E5V45QfOB3EMPe+8Jjxl3QUFuk4skgP1ggyPFiSSBMn3kNa90GVd10WBRWDXEMz8WMQ6HP1HQJkP/FITZKhRaC75Yv0W2WFIDVI0FEFTJCa+fh9KVPrJfvQo44pERTUlVRZZHD73IoQEoCWnPWRUTNNQDBbFAvoA/vUIjpTzoaKr0CWXWfhifehi4IfPtGmfTeiP6RKLFJC98BI7TZ4G/QrKFobjWIBmnGMPvEcYbyZA1FTNMEUWQef9aoyA7U+ZY1CEm6aKIpMEBX0w0eEkZYCgrAvolhRHLyLNj05bnMGUFY2HC1bY5+0N8G/sw377DOzQkmnvxIto5cciyrIX5/urq+3buxvr6kaWrV8f/mN7CA5WDJxjlE02dCHYsgb/L7BIfkUN3I4pw4TRxXlUOYtFWA4V+qonYr1IFr0kImwE2RRY7MZQt0M6V1A6A4YpozzTHOYzom5EN4lIqqBJMouQxGm6n3SHHE4xiqx3xLhMFqLcmaBKECgJmmoyifds4qot8elOK9D1JFXSWFQca6JLl86UxkBXDJFFSaUmpsyhplQVuo8hShIHVdV9LBp4uiaLEpvY1yY45FnRdS8T4hGhyjjY9Nyjojvn0gwZLkBY1LsqYWVbwvlm8Gkfna6nSbKgoGpWzPEVO+nF19R7/bKESoBITGfrHoh+esRPA1LXoUOhKx2XqIbj/O6v37+/vrPuHh4sFOpHG95tCpoidHSykTg/FLCf2vVn+7CjDtdWZAWuaaSObAqk7KmWA5opajrajqdg7wa5OcwQUJ9IQoOtmx2LdwoEtDFygmh2RcoQIEhz1LmHOLEPDq0qRN2UTV3rutI7gsRzD9DePrke2Hg0Ic6SoItw8SowDn8avDZAvWMP7a5giIahMU6WMhiIT+0koYweIhzkMwTJFZ2xTESbf6bzCUzJVE3tjLCtKKFUuQY9eV3UOKakaGEvMjIXKqc7GzUNwTB4plfqwe1OBA7nUFkzhBmSq/cpPO0sVNjhchTFJDG71TtsSdxKfAl4ze9qoETEcUIbuw49d1MT0N7YLAEywxLQNAHsPLoomAaDBVsM9mkMapqD4MUF33InseIrUma+NNAtQInFEmkEI+WuioL+YRKXgqNDKowS2nwTFRbTdi9GaBKgJchX6NAh2wHaOr+CKqJZpN0pR+9AxR4AYbrwnXb/SYKrS1S/cbbb09ak0CNoh+Cky6Qy8sgkMFj/Z+fblI6aJqMTJo6JlrDwn7KqUE4HsoYC5ufwIgbLAKF2oBp5uiCLsiGJ/O9iDeJ3Jcqck3A1K5m6YJ5Z/5V+RLcxIihwDaBxTJ1HKIZFH5gkohw9oqlzTODUIwwcBfUxQVu/CFpWWVY1U+a/IGuKkBcu7mwTlPFpWpUsVEnXlHSVf/GZ07x8WtYX39BWxjIhdllikddmAvgi7xYqTU+Vd0uCbQAdnjluZYxI8XikFkIVDAk6wXNcRxoRgr5HiaoEu5QkcUwG3iuF2xCDMrWfoqozFJKqoC83FMuxTOfwa7IGRzPHCz692N2p4CVNEKD/zfGad62ExIRBaiiGrqlzVWIJKY8eRbTxKctMzpBxcE6YglRRlmRF4thtG1UOUNNTbrShLHCGyrtuTI40pAzkE1UZDiRRmAvnhFGPcu4Yssxvwd2bAZa2E8hpBXaRo6cxBHlSfnZRk01NMRSODvgg9vj4OCFbcLotoKICA/yWpQ34lVXChB6DMhnAlY+sc0yVMQZ8UnUfRZG1dPd4Dvj1PLy0s/SlqqA60qY+SzrsFuZKV6csuyzoKMiwI5RveO8WLs930cukTVvdFDRJ6YhSHjnB38Sek6bSA9uNEzkFBvhXus1rUUJBujzryUBN5QpLWzD7K12DaZJsoGQSPKu0VOCmtlWyYncPIcZFq+cfqa9US7pumlwdxoYIucYpjaqsqqaucdykzPBWzhcAyltAefUDjmYBJRCexx33qM8QkH+go1LK8/iOHu0m+6VooASKKGcjRdSTU6S3sxw7sb2AsuaCrMMOKMhzFZKMKOtd6qqhoVT6M1UTjKhrSMEJW0DNys8GdTuork1Z0d6QDdMQNY5Gs9vNSAFTxloIgqAaIov0BUQ6pl3NGiLkJ5nzlNqo403zWVOi1gQFhVvM7TPT7hddinCCMnWFY7HBbjVP2O800Hm9ZHCs6dyt4ynHLZKkG7KpzpCl77gDnv29wJ19oqyPBa2cqnFc/g1BTgsPaH5at+GeZovJhB0bap3/oUqOPu/bucKp5kFVkWUJbYv+478ufry4/3Dz6eOHqw8Pf7HuHz6/+3Brfbq7/XR99/Dh+v7izcXfc8TgKXAu0f22y+TZPexD7xj7dpKAKGX49y9f4HP2C9jdJ4Hz9c925KLLcjH6+g36Az2A/ncR2lFyGx6Kj2+Kv/h7X1KE8FGWXg528eWPxV+cIHQh7d3Xj0FWsqD1fp9ai9//kf2BFPMOPNlHL1kZ8H/AtoIt86/XVw/W/e3nu6u0eX76w6vv/ZA39c9fLkT44sUP4ACXErCV4BefH365NL5c/OH3Xw4/5V3xB/hfaHqS7/cQHfi57KJfLuBDP/zw01Pg7UD0w8H20Y/ZQjv/Df3qeqD4Dbm6XpAmJ8gyJwax43qw5wbVyK4fjpELH0Yvvtl+hv053j6CJ/CMDtZcz36Mt+/Ayz06Ro8v631tmyOLt8N9cHuKLcPAs8USJYkAWIYQDSR98PsTnM+KvR9GH/DHwI52RarNc8HuA9HbWbLSWOfpHnXefRCLOC1082bn7JxzwR3AgQMdpNXjz468DqN3EDYzye7zNLJnGYojYDCFWAb6EdjtmgbzgW3z7oTYcR1zPowdzPuavzM8e9am70TQCbd1IjEfzhbrDOBP28x/6vKl8i3CijNV+/l0xlE+0RC3dfQxg7g4JzBl21SF75vpd5n/nZrVzbwy9GLo7FztSiUzQm0z73dFOnab51VqJ4Q+vK1b4fNibbHHwzl7R22x78PZdc98XqhdCLDRzq7YLgSjaNv3188Eug2kE3vjxvuMYBucO9HB5zb5LoQL4lnhNVmPz9q9OzQ903h+H6A2h9ceKPb2Kk+0nnmXEqk90Xrm3oWwgsNHqJ/Gg61Hb97fSErroTbFNO9Lx3PNkYHW98fQSje/ZhrBvRunxf2Lcss00922op5tKn+R1qaFfjsqb1bTfaXiNsC3pW24bb3dI89pM94/apuiMxlLBgorKxI34Y92EKjfjM36hK1BHxU0VY1lO364Pknr2HFFnW22Zy9p3T8YEfTxGGXpLdYoagkeX9gs3nalwmbgMYV1soiZNYqaQ8cUFO0ur1XSAjuuqJDq4SlYrbQn+LgC+zZ8K3YiN0yCubYN2MvdkgJX/NDzVit0jh1TVLBecwWIzBU4xnAhslpZS/SY4j7FkbNag1WCxxR2HzrRaueiEjy2sO5qG7bATiCqlSbpX7G8pQCYQj8/rXjkluCxhX1dsayvJKLmKXzWKGkOHVdQe70LgwI7rqiO7TyvcBuqiR5T3K8A1To7rFXeCnxMgYsrTWuUtsBOIOrro73axV4VP6HIWWHO9W49dsmBqwJQXtpYpeQn+LgCr9m78gi9K2/F3pVH5l35tus9Bq9rlbYCH1fg0H5+XPEhQhU/rsjxav3KHDqmoKFzWO2St8COK2q02mk3h44vaDWrw0oFroqAKXjsRHbiPIf2bq1y1yXAFRusfEqqCYAr9HpPE2Ki0wRU9Ptprthf9rKW6PHFXfER/gk9prirXhORroiOq14SHUnXRKs+BiQ9BXzZ2asdtQV2TFG/7Wa7i8Fc1AI7WWjs6oRtoseOje38uuPL1lfNK1LNG1OdkeJ5WZJpIeUtGh3PuAenI5S8fifiVATlnG3dUM2pzfsqtjSbtnU5zT27DcaUKUc6JhBKJ2c5nh3H7pObZZ9YiYA9yEcEdtcrcS/0sTZGKaTWIWIJdUwkqAJwfncI17yUYMdHY1ESfgVincBiiBW6893jZCBYCXdMtLIC6wrkKrGOCpXYyfHs2324UpVgt2N+VvvWXoThyWSj98wXusaUkScsO4EdbWMUU+B5c12tnSpYFS7emFyJXAXW0c47bZGQZjQYuG76DH/+ZkdgaG2Q0hheGuAMqCy5woyJHXrbKFPKtpA9+1y0TB3m6MKglhoqjRddvnBNuOQGFGcpWON17kmlWyvFmqmJFK/V0z6yfLkKmJwtTS1F5bTNiDyt5bDJqeXBG7vi3mWfOvzVWmq9JViqkbyfNcDFGO+WomPzqrVCbr1YVDJbmQqGRBnVQ8+7eenJlWliWBhCXaxefqpx8NsYApS9/7fS8fv7fN8W/ri/gzV/rKnnFNsgnVKQ2oq1C44ls7t6oTskwBohOIuEXa0UMhsXLaeZgl64WaqL3yhUXwowPq52p5LwKxY4h48t7hKW0lPk7V5bDwhcKTm/YrHrUvCcbGsDadmGt6GxfLppCkBkCVYscO89ryFLsGJ5+y+R92U2P//N2yny9t6+HTd8K5a6LgWF8FbyPTz/nT42KjjJQjcDpDaxnbdyeBKwwFMkS6/782dhJFNiJmxzRqhLQ6dGaGnxdYiyDy1+qd9QHcS87ZKAUl1ZhCC+yiodHm0wrLT/FYGReHKxXh2i/QWmS8NTKZG19GaEuOFGN4XA9x2KciRrF/4kwwyLiFLd65h+U501nK6qBMS9Zd1i9yRWo7ZM7gGCjY5hgrt11dfX6vU9GmeenU3j+LEbWwcom/XiRslx8T5xS1dpA9ko3qVTFKL80vU+22K1StX0CUJn5bBmRvc3oLriVAtLdxh9BzFOwKu/8EmyTxHDArGzhHlhCTYOWkFt6TrPYZaqrsDG6GlFLY4oWXr0SJ+gBXSejlep1IUbokJFhemuwMY4HVynlC6ZmPV+sypJW9CZWc56gUI29rNOc+HGpQ62MDFtEca7V6PW4+47/Ak6lRFArLLLUOtXRZ9YGEamVQszvZ6zQpUMiELcSyKQ2NEeLH0KxuoaVVmI+8PCDTJWR8CbhpqdJww38N/1Sd8rCLEKwiDwVmwPRsShUsdvRQ+URnH/G5ktT5LwXKSs2ZLmDi4DQ5rrev3SVyQhd6vgJAwOSV4jfQk3mmgUgicVs0UQagHbbWYVwV791B6KkqDrZLbRcIjdWny/XDuphUPSbVvgJ2yWp7RWcIOpqoQmbAxLhR7/CqIDWPrE3iXnCTiOOaq8sWzLUxe1hRyzVdOTvcxarbBpG+hx27f62gobuQGfq2tWGop16KlwSKqwyezb+uScNObXJy5N78fzogAI0yyZbLaRT/QWb1gLoKesGVXo473q9Hx2AzBLrLpeqRtSECsgKw67cvlLIYjFX3unrwuB4VTUX128TW1I3oWfp09RsS6r0VSZ4qsKnahnrE3WJnZm8+xxBzz7O5s5NqO1cFOTgSzMzAnyuF3NnrXsyH/RfGvvOJv71UnaQM/TsOSqXfZAy3WUG5QTZNrx1fVVXXnA30Uvw0l+dr7dfoZmTGaEFjogU0VsM4hpJz2hZdst61qTiuoo4/uqGaClFITBUWPaj0sJt20BaDdX87ZZiQpOaJnNk52pwmksI0B5jRetyErG0RIsT3vouY8T8ywCf9GLvFTE1MRVgQ6m24MPOv5xDfLkMMekAeuQBuBJs+A8HTVx+vJxNOXxlptnpSaP15NQpSkPquS3AnFymGPSoBp2K5AmhzkmTbQOSxDhWYKsXMoaBDohHZNpyTuGNZF6dgWZ5PItp+qlumpID6mPVgGK41OsQB6n525rW5q0fIG91PPQplAVtKOVW1bSWnWoYy22uEomva2FWcYkHXzL3Rqo2Yju1DTNMbW0oiz94wmvIguaym3/6XhYhSWvQB2T6gWCX26Iak2qCtTx/hctd3ek1vui7o2RDnmsPTiAaFEF4gblquLFWdevQKy+bBld6/oViNOXXa9zXb8Cebye9Ihd6/oViJPDxJBmRf5rHS3OnsUKhMph4uxZrECaCM/KLaMuOo5A/TXQe/Zh1iFTjhRPpjV5D23EeHtNKxCtJ/SG6swLp+4wiKJDYME/A3QlfNeRoZHi7LFJc6GKz08gW3CztugSgl3cMUZNt9RHXnYqpXrdvSZgPqXPFrx0a5Y87Vq7UY3kXeS+tELUG88gZ51NgN2Cjx0zRWwRwqLX9R4+MgwyW/CCraqRvOP1LtuYRVOckthOr2qfhZ0vdY44SVpot4J3rJQhenTBXadbNqxFf/6say82rWu3cAVgHOGWu7bslg1nkXl6NC0LvzoBT6hxxFz0CrRbRsyl6Onp5Z4d9wqIc4pce3rZ21dDcuIfxVZfio+Pi95oGJS4Bn5Q6Eoq/DV15E7YZIKuqkMPocfs1CvsyjgduPb0wjfQhgTF3knL31ryblq3nPjbalRbNaXfvMxVc0Un+aK5Chjb0V+TcAVgXEd/TbLhRMDW3ck1SXeCTOABr0xAnLsZfV7V+kStgydwGVYmKoGAS4597pYPPwi69VXji+bHxqFVWtqkdXTV3IDMwdZmZorjL6xzmBRREEsLSfda1VDvUUwH5tFY4NNL4DWxEjv+mmZ1hP367F0VQ+ZR/JyOo5qaPrNbPKip4mSqA/Ok3rF8mUfxz2HW+u3ZFbTAQ7bsw8HxjjvQMmaVNiqVEMIvl9EkWyTWNse+bQPcjkmzkODjXmF6I45rsiR/SzPAwm63QEHq4EZbBGX0WJ4QNWxDMqQRCr4sL1GGKrYBGfzwmKZXMRYoQw3blsB4tgze3cPtvcTEIkKLvwxNpSI1umwObqC5gxi63lkR+6WJUIE22NattrsPjpEz2HSQNFpQIepL8DxzwTPc2zo4km4+7CM8RQA0UnE3nsiyfg4NC3d8WNhJ4J9/m7oQdpvJtM2Bb0/ohux4FBwT93D2OLA+Iar4BsTYgTACjp2AnbUDTyjHKXQmzn4m3ydUP9oBEcELOCTWHuojXKxgTYwD4vwCSSBbsFRRqvgGxPDgsmepIhTYhlwgEMf2HliPx6en8y91+gRpoxzx6iCSJEi+h+cPmO4VqYVyRCS0mW97nnU4+o/g/PFUQ3J1QB0R7ltkh+HCpapiHBAHMbQfvcVOqFV8Q2JA/nBuWmyLVPENiPHXIzgutilKcAMCxMAPnxdrmE/ohkRIbOer5dvQlVtsd2piHBDnHj16s2hpGhAH2yatK7vs6b8FcmiH0I7PvsLvk6PANgQfnQ0utl+d0JHtUhRzzvAJ4g3wb+zDfvic6BnYoSWfeyujqaBCwG0uw/YEk/ys7P3V1djto7d3N9bVjSxbvz78x3gK3UNwsGLgHKNmA3ToF0myWO1CzWyrom9Pkm0L4O2EuV0OWnz2kAhqIXPso3JWfVbrRbLWKnOPHFjtnE7oS7Om2C1dosfu02uVNMeO36bLiBCY1rL9EQP9Vy6n3Dvs2vVdmEGo4tr2ga9tMi5MgCa2XiHSvbmFgS8w9YLOFqwLQ12C6oVdXz8sDH4LXK8YaPmwuA5fguqHnS0aloa7RHUCPnaS3ow8ojiNPZ1VL0Uf2alsfh5bg0e2xsOIIih4LiGQoCF/cRDfhDiwVC8f9dNK9wuXpwTJ7pA9Bvt9LZVG8/c0jvvFBd8Gx8z1+/fXd0PdJnvCunt4OPegySTengTbZti2dYhDm4fpg+fuLCNyjG2AnoRdthwFxKH9T8+KkiSffS33sAOvixWqByv1gK5/qMW1hOHGCcNZ9FDy2nbjmKc1ck4dGKB3tvPBxt/NgqPCrQMLKuA7kw0sWOUonODw5O6PkY0iVQo478CTffQSiAfyBF7tm8fAjnZX6e1m99H1YDeHPz9GO0kXFPuNsEH/vBUE+GRoR0nzQd85buzI34CnSJY2/l5S4B++pAjhoyy9HGz4WgLnM+cZomy+C5fVm0wLmzjePEUQ67cg+rrJJd+kyaQOwQN8/wq9n4GBFOEwHKK1+7pJT4ngF/Dvb8oBu7EuZVnXdVkWzUtVk01DVzWjnNB+2oHYidwQKe73P22rn7JBWFMt/O6noo3g3y/+8f8A/TiPAA===END_SIMPLICITY_STUDIO_METADATA