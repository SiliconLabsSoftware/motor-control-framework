#include "sl_event_handler.h"

#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "sl_rail_util_compatible_pa.h"
#include "sl_rail_util_power_manager_init.h"
#include "app_log.h"
#include "ble_peer_manager_peripheral.h"
#include "sl_bt_rtos_adaptation.h"
#include "sl_bluetooth.h"
#include "sl_gpio.h"
#include "sl_iostream_rtt.h"
#include "sl_iostream_stdlib_config.h"
#include "sl_mbedtls.h"
#include "psa/crypto.h"
#include "sl_se_manager.h"
#include "sli_protocol_crypto.h"
#include "sli_crypto.h"
#include "sl_iostream_init_instances.h"
#include "cmsis_os2.h"
#include "sl_iostream_handles.h"

void sli_driver_permanent_allocation(void)
{
}

void sli_service_permanent_allocation(void)
{
}

void sli_stack_permanent_allocation(void)
{
  sli_bt_stack_permanent_allocation();
}

void sli_internal_permanent_allocation(void)
{
}

void sl_platform_init(void)
{
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
}

void sli_internal_init_early(void)
{
}

void sl_kernel_start(void)
{
  sli_bt_rtos_adaptation_kernel_start();
  osKernelStart();
}

void sl_driver_init(void)
{
  sl_gpio_init();
}

void sl_service_init(void)
{
  sl_hfxo_manager_init();
  sl_iostream_stdlib_disable_buffering();
  sl_mbedtls_init();
  psa_crypto_init();
  sl_se_init();
  sli_protocol_crypto_init();
  sli_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances_stage_1();
  sl_iostream_init_instances_stage_2();
}

void sl_stack_init(void)
{
  sl_rail_util_pa_init();
  sl_rail_util_power_manager_init();
  sli_bt_stack_functional_init();
}

void sl_internal_app_init(void)
{
  app_log_init();
  ble_peer_manager_peripheral_init();
}

void sl_iostream_init_instances_stage_1(void)
{
  sl_iostream_rtt_init();
}

void sl_iostream_init_instances_stage_2(void)
{
  sl_iostream_set_console_instance();
}

