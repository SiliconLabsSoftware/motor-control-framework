/***************************************************************************//**
 * @file ble_stream_adapter.h
 * @brief BLE Stream adapter – Stream API and buffers only (no BLE init/GATT)
 *******************************************************************************
 * Use this adapter when BLE stack init, GATT DB, advertising and other
 * characteristics are handled elsewhere (e.g. SiSDK autogen / app code).
 *
 * Integration:
 * 1. Create the adapter (e.g. global or next to Commander).
 * 2. In your GATT write handler for the SPP/command characteristic, call
 *    pushReceivedData(data, len).
 * 3. Call setSendCallback() with a function that sends (conn, data, len) via
 *    sl_bt_gatt_server_send_notification (or notify all).
 * 4. In the motor loop call commander.run(bleStreamAdapter).
 ******************************************************************************/

 #ifndef BLE_STREAM_ADAPTER_H
 #define BLE_STREAM_ADAPTER_H

 #include "Arduino.h"
 #include "FreeRTOS.h"
 #include "semphr.h"
 #include <cstddef>
 #include <cstdint>

/** Send callback: (connection_handle, data, length). Use 0xFF for "all connections" if your API supports it. */
using BleStreamSendFn = void (*)(uint8_t connection, const uint8_t *data, size_t len);

/**
 * Check-send-condition callback: called after each byte is stored during write().
 * @param index  index of the current byte in buffer (0-based)
 * @param buffer the full write() buffer
 * @param size   total size of the write() buffer
 * @return true to flush immediately after this byte
 */
using BleStreamCheckSendFn = bool (*)(size_t index, const uint8_t *buffer, size_t size);

/**
 * Stream implementation backed by RX/TX ring buffers.
 * No BLE stack, GATT or advertising – only buffers and Stream API.
 * Thread-safe for one producer (BLE event) and one consumer (Commander / main loop).
 */
class BleStreamAdapter: public Stream
{
public:
  static constexpr size_t DEFAULT_RX_SIZE = 512u;
  static constexpr size_t DEFAULT_TX_SIZE = 512u;
  static constexpr size_t DEFAULT_MAX_SEND_CHUNK = 20u;
  static constexpr size_t MAX_BLE_PDU = 250u;

  /** Fixed-size buffers (no heap). Use DEFAULT_RX_SIZE / DEFAULT_TX_SIZE. */
  BleStreamAdapter();

  ~BleStreamAdapter();

  // --- Stream (read path: Commander reads from here) ---
  int available() override;
  int read() override;
  int peek() override;

  // --- Print (write path: Commander prints responses here) ---
  size_t write(uint8_t data) override;
  size_t write(const uint8_t *buffer, size_t size) override;

  /**
   * Push data received from BLE (e.g. in GATT write handler).
   * Call from your sl_bt_evt_gatt_server_attribute_value handler for the command characteristic.
   */
  void pushReceivedData(const uint8_t *data, size_t len);

  /**
   * Set callback used to send TX data. Called when flushing (e.g. after write or flushTx).
   * Your callback should call sl_bt_gatt_server_send_notification(conn, char_handle, len, data).
   */
  void setSendCallback(BleStreamSendFn send_fn);

  /**
   * Set the check-send-condition callback. Called per byte inside write() to decide when to flush.
   * If not set, falls back to flushing when buffer reaches max_send_chunk_ bytes.
   */
  void onCheckSendCondition(BleStreamCheckSendFn check_fn);

  /**
   * Set max bytes sent per notification. Must be <= your GATT characteristic max length
   * Default is DEFAULT_MAX_SEND_CHUNK (20). Call before sending.
   */
  void setMaxSendChunk(size_t max_chunk);

  /**
   * Flush buffered TX data via the send callback. Call from main loop if you want
   * to send after a batch of writes (optional – write() can flush automatically).
   */
  void flushTx();

private:
  BleStreamAdapter(const BleStreamAdapter &) = delete;
  BleStreamAdapter &operator = (const BleStreamAdapter &) = delete;

  void flushTxInternal();

  size_t rx_size_;
  size_t tx_size_;
  uint8_t rx_buf_[DEFAULT_RX_SIZE];
  uint8_t tx_buf_[DEFAULT_TX_SIZE];
  size_t rx_head_;
  size_t rx_tail_;
  size_t tx_head_;
  size_t tx_tail_;
  BleStreamSendFn send_cb_;
  BleStreamCheckSendFn check_send_cb_;
  size_t max_send_chunk_;

  SemaphoreHandle_t rx_mutex_;
  SemaphoreHandle_t tx_mutex_;
  StaticSemaphore_t rx_mutex_buf_;
  StaticSemaphore_t tx_mutex_buf_;
};

/** Single shared instance. Defined in ble_stream_adapter.cpp. */
extern BleStreamAdapter bleStreamAdapter;

 #endif /* BLE_STREAM_ADAPTER_H */
