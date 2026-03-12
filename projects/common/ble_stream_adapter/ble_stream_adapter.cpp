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
  return cap - ring_available(head, tail, cap) - 1u;   // one slot reserved
}

BleStreamAdapter::BleStreamAdapter()
  : rx_size_(DEFAULT_RX_SIZE),
  tx_size_(DEFAULT_TX_SIZE),
  rx_head_(0),
  rx_tail_(0),
  tx_head_(0),
  tx_tail_(0),
  send_cb_(nullptr),
  check_send_cb_(nullptr),
  max_send_chunk_(DEFAULT_MAX_SEND_CHUNK),
  rx_mutex_(nullptr),
  tx_mutex_(nullptr)
{
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
}

int BleStreamAdapter::available()
{
  if (!rx_mutex_) {
    return 0;
  }
  xSemaphoreTake(rx_mutex_, portMAX_DELAY);
  int n = static_cast < int > (ring_available(rx_head_, rx_tail_, rx_size_));
  xSemaphoreGive(rx_mutex_);
  return n;
}

int BleStreamAdapter::read()
{
  if (!rx_mutex_) {
    return -1;
  }
  xSemaphoreTake(rx_mutex_, portMAX_DELAY);
  if (ring_available(rx_head_, rx_tail_, rx_size_) == 0) {
    xSemaphoreGive(rx_mutex_);
    return -1;
  }
  int byte = static_cast < int > (rx_buf_[rx_tail_]);
  rx_tail_ = (rx_tail_ + 1) % rx_size_;
  xSemaphoreGive(rx_mutex_);
  return byte;
}

int BleStreamAdapter::peek()
{
  if (!rx_mutex_) {
    return -1;
  }
  xSemaphoreTake(rx_mutex_, portMAX_DELAY);
  if (ring_available(rx_head_, rx_tail_, rx_size_) == 0) {
    xSemaphoreGive(rx_mutex_);
    return -1;
  }
  int byte = static_cast < int > (rx_buf_[rx_tail_]);
  xSemaphoreGive(rx_mutex_);
  return byte;
}

void BleStreamAdapter::pushReceivedData(const uint8_t *data, size_t len)
{
  if (!rx_mutex_ || !data) {
    return;
  }
  xSemaphoreTake(rx_mutex_, portMAX_DELAY);
  for (size_t i = 0; i < len; i++) {
    size_t free_count = ring_free(rx_head_, rx_tail_, rx_size_);
    if (free_count == 0) {
      break;   // overflow, drop
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
  if (!tx_mutex_ || !buffer) {
    return 0;
  }
  size_t written = 0;
  for (; written < size; written++) {
    xSemaphoreTake(tx_mutex_, portMAX_DELAY);
    if (ring_free(tx_head_, tx_tail_, tx_size_) == 0) {
      xSemaphoreGive(tx_mutex_);
      break;
    }
    tx_buf_[tx_head_] = buffer[written];
    tx_head_ = (tx_head_ + 1) % tx_size_;
    size_t avail = ring_available(tx_head_, tx_tail_, tx_size_);
    xSemaphoreGive(tx_mutex_);

    bool do_flush = false;
    if (check_send_cb_) {
      // User-supplied condition (e.g. flush on \r or \n), matching sppBLE sendReady
      do_flush = check_send_cb_(written, buffer, size);
    }
    // Fallback: flush when buffer reaches a full chunk (handles output without \r\n)
    if (!do_flush && avail >= max_send_chunk_) {
      do_flush = true;
    }
    if (do_flush) {
      flushTxInternal();
    }
  }
  return written;
}

void BleStreamAdapter::setSendCallback(BleStreamSendFn send_fn)
{
  send_cb_ = send_fn;
}

void BleStreamAdapter::onCheckSendCondition(BleStreamCheckSendFn check_fn)
{
  check_send_cb_ = check_fn;
}

void BleStreamAdapter::setMaxSendChunk(size_t max_chunk)
{
  if (max_chunk == 0u) {
    max_chunk = 1u;
  }
  if (max_chunk > MAX_BLE_PDU) {
    max_chunk = MAX_BLE_PDU;
  }
  max_send_chunk_ = max_chunk;
}

void BleStreamAdapter::flushTx()
{
  flushTxInternal();
}

void BleStreamAdapter::flushTxInternal()
{
  if (!send_cb_ || !tx_mutex_) {
    return;
  }
  uint8_t tmp[MAX_BLE_PDU];
  for (;; ) {
    xSemaphoreTake(tx_mutex_, portMAX_DELAY);
    size_t n = ring_available(tx_head_, tx_tail_, tx_size_);
    if (n == 0) {
      xSemaphoreGive(tx_mutex_);
      return;
    }
    size_t chunk = (n > max_send_chunk_) ? max_send_chunk_ : n;
    for (size_t i = 0; i < chunk; i++) {
      tmp[i] = tx_buf_[tx_tail_];
      tx_tail_ = (tx_tail_ + 1) % tx_size_;
    }
    xSemaphoreGive(tx_mutex_);
    send_cb_(0xFF, tmp, chunk);   // 0xFF = all connections; app can use single conn if needed
  }
}
