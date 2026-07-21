/***************************************************************************//**
 * @file sl_lsm6dsm.c
 * @brief LSM6DSM IMU Driver - Simple SPI Implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_lsm6dsm.h"
#include "lsm6dsm_reg.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define LSM6DSM_BOOT_TIME_MS   15  /**< Sensor boot time in milliseconds */

/*******************************************************************************
 ***************************   LOCAL VARIABLES   *******************************
 ******************************************************************************/

static SPIDRV_Handle_t spi_handle = NULL;
static GPIO_Port_TypeDef cs_port;
static unsigned int cs_pin;
static stmdev_ctx_t dev_ctx;
static sl_lsm6dsm_accel_fs_t current_accel_fs = SL_LSM6DSM_ACCEL_FS_2G;
static sl_lsm6dsm_gyro_fs_t current_gyro_fs = SL_LSM6DSM_GYRO_FS_250DPS;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief Write to device register via SPI
 ******************************************************************************/
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  (void)handle; // Unused parameter
  Ecode_t status;

  // Assert CS (active low)
  GPIO_PinOutClear(cs_port, cs_pin);

  // Transmit register address (MSB = 0 for write)
  status = SPIDRV_MTransmitB(spi_handle, &reg, 1);
  if (status != ECODE_EMDRV_SPIDRV_OK) {
    GPIO_PinOutSet(cs_port, cs_pin);
    return -1;
  }

  // Transmit data
  status = SPIDRV_MTransmitB(spi_handle, bufp, len);

  // Deassert CS
  GPIO_PinOutSet(cs_port, cs_pin);

  return (status == ECODE_EMDRV_SPIDRV_OK) ? 0 : -1;
}

/***************************************************************************//**
 * @brief Read from device register via SPI
 ******************************************************************************/
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  (void)handle; // Unused parameter
  Ecode_t status;

  // Set read bit (bit 7) for SPI read operation
  reg |= 0x80;

  // Assert CS (active low)
  GPIO_PinOutClear(cs_port, cs_pin);

  // Transmit register address
  status = SPIDRV_MTransmitB(spi_handle, &reg, 1);
  if (status != ECODE_EMDRV_SPIDRV_OK) {
    GPIO_PinOutSet(cs_port, cs_pin);
    return -1;
  }

  // Receive data
  status = SPIDRV_MReceiveB(spi_handle, bufp, len);

  // Deassert CS
  GPIO_PinOutSet(cs_port, cs_pin);

  return (status == ECODE_EMDRV_SPIDRV_OK) ? 0 : -1;
}

/***************************************************************************//**
 * @brief Convert ODR enum to register value
 ******************************************************************************/
static lsm6dsm_odr_xl_t convert_accel_odr(sl_lsm6dsm_odr_t odr)
{
  switch (odr) {
    case SL_LSM6DSM_ODR_OFF:    return LSM6DSM_XL_ODR_OFF;
    case SL_LSM6DSM_ODR_12_5HZ: return LSM6DSM_XL_ODR_12Hz5;
    case SL_LSM6DSM_ODR_26HZ:   return LSM6DSM_XL_ODR_26Hz;
    case SL_LSM6DSM_ODR_52HZ:   return LSM6DSM_XL_ODR_52Hz;
    case SL_LSM6DSM_ODR_104HZ:  return LSM6DSM_XL_ODR_104Hz;
    case SL_LSM6DSM_ODR_208HZ:  return LSM6DSM_XL_ODR_208Hz;
    case SL_LSM6DSM_ODR_416HZ:  return LSM6DSM_XL_ODR_416Hz;
    case SL_LSM6DSM_ODR_833HZ:  return LSM6DSM_XL_ODR_833Hz;
    case SL_LSM6DSM_ODR_1666HZ: return LSM6DSM_XL_ODR_1k66Hz;
    case SL_LSM6DSM_ODR_3333HZ: return LSM6DSM_XL_ODR_3k33Hz;
    case SL_LSM6DSM_ODR_6666HZ: return LSM6DSM_XL_ODR_6k66Hz;
    default:                    return LSM6DSM_XL_ODR_OFF;
  }
}

/***************************************************************************//**
 * @brief Convert ODR enum to gyro register value
 ******************************************************************************/
static lsm6dsm_odr_g_t convert_gyro_odr(sl_lsm6dsm_odr_t odr)
{
  switch (odr) {
    case SL_LSM6DSM_ODR_OFF:    return LSM6DSM_GY_ODR_OFF;
    case SL_LSM6DSM_ODR_12_5HZ: return LSM6DSM_GY_ODR_12Hz5;
    case SL_LSM6DSM_ODR_26HZ:   return LSM6DSM_GY_ODR_26Hz;
    case SL_LSM6DSM_ODR_52HZ:   return LSM6DSM_GY_ODR_52Hz;
    case SL_LSM6DSM_ODR_104HZ:  return LSM6DSM_GY_ODR_104Hz;
    case SL_LSM6DSM_ODR_208HZ:  return LSM6DSM_GY_ODR_208Hz;
    case SL_LSM6DSM_ODR_416HZ:  return LSM6DSM_GY_ODR_416Hz;
    case SL_LSM6DSM_ODR_833HZ:  return LSM6DSM_GY_ODR_833Hz;
    case SL_LSM6DSM_ODR_1666HZ: return LSM6DSM_GY_ODR_1k66Hz;
    case SL_LSM6DSM_ODR_3333HZ: return LSM6DSM_GY_ODR_3k33Hz;
    case SL_LSM6DSM_ODR_6666HZ: return LSM6DSM_GY_ODR_6k66Hz;
    default:                    return LSM6DSM_GY_ODR_OFF;
  }
}

/***************************************************************************//**
 * @brief Convert full scale enum to register value
 ******************************************************************************/
static lsm6dsm_fs_xl_t convert_accel_fs(sl_lsm6dsm_accel_fs_t fs)
{
  switch (fs) {
    case SL_LSM6DSM_ACCEL_FS_2G:  return LSM6DSM_2g;
    case SL_LSM6DSM_ACCEL_FS_4G:  return LSM6DSM_4g;
    case SL_LSM6DSM_ACCEL_FS_8G:  return LSM6DSM_8g;
    case SL_LSM6DSM_ACCEL_FS_16G: return LSM6DSM_16g;
    default:                      return LSM6DSM_2g;
  }
}

/***************************************************************************//**
 * @brief Convert gyro full scale enum to register value
 ******************************************************************************/
static lsm6dsm_fs_g_t convert_gyro_fs(sl_lsm6dsm_gyro_fs_t fs)
{
  switch (fs) {
    case SL_LSM6DSM_GYRO_FS_125DPS:  return LSM6DSM_125dps;
    case SL_LSM6DSM_GYRO_FS_250DPS:  return LSM6DSM_250dps;
    case SL_LSM6DSM_GYRO_FS_500DPS:  return LSM6DSM_500dps;
    case SL_LSM6DSM_GYRO_FS_1000DPS: return LSM6DSM_1000dps;
    case SL_LSM6DSM_GYRO_FS_2000DPS: return LSM6DSM_2000dps;
    default:                         return LSM6DSM_250dps;
  }
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize the LSM6DSM sensor
 ******************************************************************************/
sl_status_t sl_lsm6dsm_init(const sl_lsm6dsm_config_t *config)
{
  uint8_t whoami;
  uint8_t rst;

  if (config == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // Store configuration
  spi_handle = config->spi_handle;
  cs_port = config->cs_port;
  cs_pin = config->cs_pin;

  // Configure CS pin as output, initially high (inactive)
  GPIO_PinModeSet(cs_port, cs_pin, gpioModePushPull, 1);
  GPIO_PinOutSet(cs_port, cs_pin);

  GPIO_PinModeSet(gpioPortC, 6, gpioModeInputPull, 1);

  // Initialize device context
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &spi_handle;

  // Check device ID
  if (lsm6dsm_device_id_get(&dev_ctx, &whoami) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  if (whoami != LSM6DSM_ID) {
    return SL_STATUS_INVALID_SIGNATURE;
  }

  // Perform software reset
  if (lsm6dsm_reset_set(&dev_ctx, PROPERTY_ENABLE) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Wait for reset to complete
  do {
    if (lsm6dsm_reset_get(&dev_ctx, &rst) != 0) {
      return SL_STATUS_TRANSMIT;
    }
  } while (rst);

  // Enable Block Data Update
  if (lsm6dsm_block_data_update_set(&dev_ctx, PROPERTY_ENABLE) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Set default full scale ranges
  current_accel_fs = SL_LSM6DSM_ACCEL_FS_2G;
  current_gyro_fs = SL_LSM6DSM_GYRO_FS_250DPS;

  if (lsm6dsm_xl_full_scale_set(&dev_ctx, convert_accel_fs(current_accel_fs)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  if (lsm6dsm_gy_full_scale_set(&dev_ctx, convert_gyro_fs(current_gyro_fs)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Deinitialize the LSM6DSM sensor
 ******************************************************************************/
sl_status_t sl_lsm6dsm_deinit(void)
{
  // Power down accelerometer and gyroscope
  if (lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  if (lsm6dsm_gy_data_rate_set(&dev_ctx, LSM6DSM_GY_ODR_OFF) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  spi_handle = NULL;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Configure the sensor sampling rate
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_sample_rate(sl_lsm6dsm_odr_t accel_odr,
                                       sl_lsm6dsm_odr_t gyro_odr)
{
  // Set accelerometer ODR
  if (lsm6dsm_xl_data_rate_set(&dev_ctx, convert_accel_odr(accel_odr)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Set gyroscope ODR
  if (lsm6dsm_gy_data_rate_set(&dev_ctx, convert_gyro_odr(gyro_odr)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Set accelerometer full scale range
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_accel_full_scale(sl_lsm6dsm_accel_fs_t fs)
{
  current_accel_fs = fs;

  if (lsm6dsm_xl_full_scale_set(&dev_ctx, convert_accel_fs(fs)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Set gyroscope full scale range
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_gyro_full_scale(sl_lsm6dsm_gyro_fs_t fs)
{
  current_gyro_fs = fs;

  if (lsm6dsm_gy_full_scale_set(&dev_ctx, convert_gyro_fs(fs)) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Check if new accelerometer data is available
 ******************************************************************************/
bool sl_lsm6dsm_is_accel_data_ready(void)
{
  uint8_t reg;

  if (lsm6dsm_xl_flag_data_ready_get(&dev_ctx, &reg) != 0) {
    return false;
  }

  return (reg != 0);
}

/***************************************************************************//**
 * Check if new gyroscope data is available
 ******************************************************************************/
bool sl_lsm6dsm_is_gyro_data_ready(void)
{
  uint8_t reg;

  if (lsm6dsm_gy_flag_data_ready_get(&dev_ctx, &reg) != 0) {
    return false;
  }

  return (reg != 0);
}

/***************************************************************************//**
 * Read accelerometer data
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_acceleration(sl_lsm6dsm_data_t *data)
{
  int16_t raw_data[3];

  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // Read raw acceleration data
  if (lsm6dsm_acceleration_raw_get(&dev_ctx, raw_data) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Convert to mg based on current full scale setting
  switch (current_accel_fs) {
    case SL_LSM6DSM_ACCEL_FS_2G:
      data->x = lsm6dsm_from_fs2g_to_mg(raw_data[0]);
      data->y = lsm6dsm_from_fs2g_to_mg(raw_data[1]);
      data->z = lsm6dsm_from_fs2g_to_mg(raw_data[2]);
      break;

    case SL_LSM6DSM_ACCEL_FS_4G:
      data->x = lsm6dsm_from_fs4g_to_mg(raw_data[0]);
      data->y = lsm6dsm_from_fs4g_to_mg(raw_data[1]);
      data->z = lsm6dsm_from_fs4g_to_mg(raw_data[2]);
      break;

    case SL_LSM6DSM_ACCEL_FS_8G:
      data->x = lsm6dsm_from_fs8g_to_mg(raw_data[0]);
      data->y = lsm6dsm_from_fs8g_to_mg(raw_data[1]);
      data->z = lsm6dsm_from_fs8g_to_mg(raw_data[2]);
      break;

    case SL_LSM6DSM_ACCEL_FS_16G:
      data->x = lsm6dsm_from_fs16g_to_mg(raw_data[0]);
      data->y = lsm6dsm_from_fs16g_to_mg(raw_data[1]);
      data->z = lsm6dsm_from_fs16g_to_mg(raw_data[2]);
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Read gyroscope data
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_gyro(sl_lsm6dsm_data_t *data)
{
  int16_t raw_data[3];

  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // Read raw gyroscope data
  if (lsm6dsm_angular_rate_raw_get(&dev_ctx, raw_data) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Convert to mdps based on current full scale setting
  switch (current_gyro_fs) {
    case SL_LSM6DSM_GYRO_FS_125DPS:
      data->x = lsm6dsm_from_fs125dps_to_mdps(raw_data[0]);
      data->y = lsm6dsm_from_fs125dps_to_mdps(raw_data[1]);
      data->z = lsm6dsm_from_fs125dps_to_mdps(raw_data[2]);
      break;

    case SL_LSM6DSM_GYRO_FS_250DPS:
      data->x = lsm6dsm_from_fs250dps_to_mdps(raw_data[0]);
      data->y = lsm6dsm_from_fs250dps_to_mdps(raw_data[1]);
      data->z = lsm6dsm_from_fs250dps_to_mdps(raw_data[2]);
      break;

    case SL_LSM6DSM_GYRO_FS_500DPS:
      data->x = lsm6dsm_from_fs500dps_to_mdps(raw_data[0]);
      data->y = lsm6dsm_from_fs500dps_to_mdps(raw_data[1]);
      data->z = lsm6dsm_from_fs500dps_to_mdps(raw_data[2]);
      break;

    case SL_LSM6DSM_GYRO_FS_1000DPS:
      data->x = lsm6dsm_from_fs1000dps_to_mdps(raw_data[0]);
      data->y = lsm6dsm_from_fs1000dps_to_mdps(raw_data[1]);
      data->z = lsm6dsm_from_fs1000dps_to_mdps(raw_data[2]);
      break;

    case SL_LSM6DSM_GYRO_FS_2000DPS:
      data->x = lsm6dsm_from_fs2000dps_to_mdps(raw_data[0]);
      data->y = lsm6dsm_from_fs2000dps_to_mdps(raw_data[1]);
      data->z = lsm6dsm_from_fs2000dps_to_mdps(raw_data[2]);
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Read accelerometer data (raw)
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_acceleration_raw(int16_t *x, int16_t *y, int16_t *z)
{
  int16_t raw_data[3];

  if (x == NULL || y == NULL || z == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (lsm6dsm_acceleration_raw_get(&dev_ctx, raw_data) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  *x = raw_data[0];
  *y = raw_data[1];
  *z = raw_data[2];

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Read gyroscope data (raw)
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_gyro_raw(int16_t *x, int16_t *y, int16_t *z)
{
  int16_t raw_data[3];

  if (x == NULL || y == NULL || z == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (lsm6dsm_angular_rate_raw_get(&dev_ctx, raw_data) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  *x = raw_data[0];
  *y = raw_data[1];
  *z = raw_data[2];

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Read device ID
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_device_id(uint8_t *device_id)
{
  if (device_id == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (lsm6dsm_device_id_get(&dev_ctx, device_id) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Perform software reset
 ******************************************************************************/
sl_status_t sl_lsm6dsm_reset(void)
{
  uint8_t rst;

  if (lsm6dsm_reset_set(&dev_ctx, PROPERTY_ENABLE) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  // Wait for reset to complete
  do {
    if (lsm6dsm_reset_get(&dev_ctx, &rst) != 0) {
      return SL_STATUS_TRANSMIT;
    }
  } while (rst);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Enable or disable Block Data Update
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_block_data_update(bool enable)
{
  if (lsm6dsm_block_data_update_set(&dev_ctx, enable ? PROPERTY_ENABLE : PROPERTY_DISABLE) != 0) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}
