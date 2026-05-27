/***************************************************************************//**
 * @file ble_handler.cpp
 * @brief BLE stack event handler (C++ so it can use BleStreamAdapter).
 *******************************************************************************
 * sl_bt_on_event is exported with extern "C" so the C BLE stack can call it.
 ******************************************************************************/

#include "ble_handler.h"
#include "ble_stream_adapter.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "sl_bt_api.h"
#include "gatt_db.h"
#include "ble_peer_manager_peripheral.h"
#ifdef __cplusplus
}
#endif

static const char BLE_DEVICE_NAME_DEFAULT[] = "motor_123456";
static const char BLE_DEVICE_NAME_PREFIX[] = "motor_";

static void handle_conn_open(sl_bt_evt_connection_opened_t *evt)
{
  (void)evt;
  // Connection opened, do nothing
}

static void handle_conn_close(sl_bt_evt_connection_closed_t *evt)
{
  (void)evt;
  // Connection closed, start advertising again
  ble_peer_manager_peripheral_create_connection();
}

static void handle_gatt_server_attribute_value(sl_bt_evt_gatt_server_attribute_value_t *evt)
{
  switch (evt->attribute) {
    case gattdb_spp_data:
      bleStreamAdapter.pushReceivedData(evt->value.data, evt->value.len);
      break;

    default:
      break;
  }
}

static void send_callback(uint8_t connection, const uint8_t *data, size_t len)
{
  if (connection == 0xFF) {
    sl_bt_gatt_server_notify_all(gattdb_spp_data, len, data);
  } else {
    sl_bt_gatt_server_send_notification(connection, gattdb_spp_data, len, data);
  }
}

/**
 * Controls when buffered TX data is flushed as a BLE notification.
 * Called after each byte is written to the TX buffer.
 *
 * Return true to send all buffered data immediately as a BLE notification.
 *
 * Replace this function body with custom logic if a different
 * packetization strategy is needed.
 */
static bool ble_check_send_condition(size_t index, const uint8_t *buf, size_t size)
{
  return buf && index < size && (buf[index] == '\r' || buf[index] == '\n');
}

static void set_ble_device_name_from_mac(void)
{
  uint8_t name_buf[gattdb_device_name_len];
  bd_addr addr;
  uint8_t addr_type;
  sl_status_t status;

  status = sl_bt_gap_get_identity_address(&addr, &addr_type);
  if (status != SL_STATUS_OK) {
    memcpy(name_buf, BLE_DEVICE_NAME_DEFAULT, sizeof(name_buf));
    sl_bt_gatt_server_write_attribute_value(gattdb_device_name, 0, sizeof(name_buf), name_buf);
    return;
  }

  // "motor_" (6 chars) + 6 lowercase hex from last 3 bytes (addr[3], addr[4], addr[5])
  memcpy(name_buf, BLE_DEVICE_NAME_PREFIX, sizeof(BLE_DEVICE_NAME_PREFIX));
  static const char hex[] = "0123456789abcdef";
  name_buf[6]  = hex[(addr.addr[2] >> 4) & 0x0F];
  name_buf[7]  = hex[addr.addr[2] & 0x0F];
  name_buf[8]  = hex[(addr.addr[1] >> 4) & 0x0F];
  name_buf[9]  = hex[addr.addr[1] & 0x0F];
  name_buf[10] = hex[(addr.addr[0] >> 4) & 0x0F];
  name_buf[11] = hex[addr.addr[0] & 0x0F];

  sl_bt_gatt_server_write_attribute_value(gattdb_device_name, 0, gattdb_device_name_len, name_buf);
}

extern "C" void sl_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      bleStreamAdapter.setSendCallback(send_callback);
      bleStreamAdapter.setMaxSendChunk(gattdb_spp_data_len);
      bleStreamAdapter.onCheckSendCondition(ble_check_send_condition);
      set_ble_device_name_from_mac();
      ble_peer_manager_peripheral_create_connection();
      break;

    case sl_bt_evt_connection_opened_id:
      handle_conn_open(&evt->data.evt_connection_opened);
      break;

    case sl_bt_evt_connection_closed_id:
      handle_conn_close(&evt->data.evt_connection_closed);
      break;

    case sl_bt_evt_gatt_server_attribute_value_id:
      handle_gatt_server_attribute_value(&evt->data.evt_gatt_server_attribute_value);
      break;

    default:
      break;
  }
}
