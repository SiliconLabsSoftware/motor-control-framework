/***************************************************************************//**
 * @file ble_stream_adapter.cpp
 * @brief BLE Stream adapter implementation (buffers + Stream API only)
 ******************************************************************************/

 #include "ble_stream_adapter.h"

 BleStreamAdapter bleStreamAdapter;
 
 // Ring buffer helpers (single producer, single consumer; mutex for cross-task safety)
 static size_t ring_available(size_t head, size_t tail, size_t cap)
 {
   size_t n = (head >= tail) ? (head - tail) : (cap - tail + head);
   return n;
 }
 
 static size_t ring_free(size_t head, size_t tail, size_t cap)
 {
   return cap - ring_available(head, tail, cap) - 1u;  // one slot reserved
 }
 
 BleStreamAdapter::BleStreamAdapter(size_t rx_buffer_size, size_t tx_buffer_size)
   : rx_size_(rx_buffer_size),
     tx_size_(tx_buffer_size),
     rx_buf_(nullptr),
     tx_buf_(nullptr),
     rx_head_(0),
     rx_tail_(0),
     tx_head_(0),
     tx_tail_(0),
     send_cb_(nullptr),
     rx_mutex_(nullptr),
     tx_mutex_(nullptr)
 {
   rx_buf_ = new uint8_t[rx_size_];
   tx_buf_ = new uint8_t[tx_size_];
   rx_mutex_ = xSemaphoreCreateMutexStatic(&rx_mutex_buf_);
   tx_mutex_ = xSemaphoreCreateMutexStatic(&tx_mutex_buf_);
   configASSERT(rx_mutex_ != nullptr);
   configASSERT(tx_mutex_ != nullptr);
 }
 
 BleStreamAdapter::~BleStreamAdapter()
 {
   if (rx_mutex_) {
     vSemaphoreDelete(rx_mutex_);
     rx_mutex_ = nullptr;
   }
   if (tx_mutex_) {
     vSemaphoreDelete(tx_mutex_);
     tx_mutex_ = nullptr;
   }
   delete[] rx_buf_;
   rx_buf_ = nullptr;
   delete[] tx_buf_;
   tx_buf_ = nullptr;
 }
 
 int BleStreamAdapter::available()
 {
   if (!rx_buf_ || !rx_mutex_) {
     return 0;
   }
   xSemaphoreTake(rx_mutex_, portMAX_DELAY);
   int n = static_cast<int>(ring_available(rx_head_, rx_tail_, rx_size_));
   xSemaphoreGive(rx_mutex_);
   return n;
 }
 
 int BleStreamAdapter::read()
 {
   if (!rx_buf_ || !rx_mutex_) {
     return -1;
   }
   xSemaphoreTake(rx_mutex_, portMAX_DELAY);
   if (ring_available(rx_head_, rx_tail_, rx_size_) == 0) {
     xSemaphoreGive(rx_mutex_);
     return -1;
   }
   int byte = static_cast<int>(rx_buf_[rx_tail_]);
   rx_tail_ = (rx_tail_ + 1) % rx_size_;
   xSemaphoreGive(rx_mutex_);
   return byte;
 }
 
 int BleStreamAdapter::peek()
 {
   if (!rx_buf_ || !rx_mutex_) {
     return -1;
   }
   xSemaphoreTake(rx_mutex_, portMAX_DELAY);
   if (ring_available(rx_head_, rx_tail_, rx_size_) == 0) {
     xSemaphoreGive(rx_mutex_);
     return -1;
   }
   int byte = static_cast<int>(rx_buf_[rx_tail_]);
   xSemaphoreGive(rx_mutex_);
   return byte;
 }
 
 void BleStreamAdapter::pushReceivedData(const uint8_t *data, size_t len)
 {
   if (!rx_buf_ || !rx_mutex_ || !data) {
     return;
   }
   xSemaphoreTake(rx_mutex_, portMAX_DELAY);
   for (size_t i = 0; i < len; i++) {
     size_t free_count = ring_free(rx_head_, rx_tail_, rx_size_);
     if (free_count == 0) {
       break;  // overflow, drop
     }
     rx_buf_[rx_head_] = data[i];
     rx_head_ = (rx_head_ + 1) % rx_size_;
   }
   xSemaphoreGive(rx_mutex_);
 }
 
 size_t BleStreamAdapter::write(uint8_t data)
 {
   return write(&data, 1);
 }
 
 size_t BleStreamAdapter::write(const uint8_t *buffer, size_t size)
 {
   if (!tx_buf_ || !tx_mutex_ || !buffer) {
     return 0;
   }
   xSemaphoreTake(tx_mutex_, portMAX_DELAY);
   size_t written = 0;
   for (; written < size; written++) {
     if (ring_free(tx_head_, tx_tail_, tx_size_) == 0) {
       break;
     }
     tx_buf_[tx_head_] = buffer[written];
     tx_head_ = (tx_head_ + 1) % tx_size_;
   }
   xSemaphoreGive(tx_mutex_);
   flushTxInternal();
   return written;
 }
 
 void BleStreamAdapter::setSendCallback(BleStreamSendFn send_fn)
 {
   send_cb_ = send_fn;
 }
 
 void BleStreamAdapter::flushTx()
 {
   flushTxInternal();
 }
 
 void BleStreamAdapter::flushTxInternal()
 {
   if (!send_cb_ || !tx_buf_ || !tx_mutex_) {
     return;
   }
   xSemaphoreTake(tx_mutex_, portMAX_DELAY);
   size_t n = ring_available(tx_head_, tx_tail_, tx_size_);
   if (n == 0) {
     xSemaphoreGive(tx_mutex_);
     return;
   }
   size_t chunk = (n > MAX_BLE_PDU) ? MAX_BLE_PDU : n;
   uint8_t tmp[MAX_BLE_PDU];
   for (size_t i = 0; i < chunk; i++) {
     tmp[i] = tx_buf_[tx_tail_];
     tx_tail_ = (tx_tail_ + 1) % tx_size_;
   }
   xSemaphoreGive(tx_mutex_);
   send_cb_(0xFF, tmp, chunk);  // 0xFF = all connections; app can use single conn if needed
 }
 