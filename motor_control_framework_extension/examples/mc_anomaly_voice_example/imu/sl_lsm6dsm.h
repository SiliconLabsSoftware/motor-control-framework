/***************************************************************************//**
 * @file sl_lsm6dsm.h
 * @brief LSM6DSM IMU Driver - Simple SPI Interface
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

#ifndef SL_LSM6DSM_H
#define SL_LSM6DSM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "spidrv.h"
#include "em_gpio.h"

/***************************************************************************//**
 * @addtogroup lsm6dsm LSM6DSM - 6-axis IMU Driver
 * @brief Simple SPI-only driver for LSM6DSM 6-axis IMU
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief LSM6DSM configuration structure
 ******************************************************************************/
typedef struct {
  SPIDRV_Handle_t spi_handle;        /**< SPI driver handle */
  GPIO_Port_TypeDef cs_port;         /**< Chip select port */
  unsigned int cs_pin;               /**< Chip select pin */
} sl_lsm6dsm_config_t;

/***************************************************************************//**
 * @brief Accelerometer full scale options
 ******************************************************************************/
typedef enum {
  SL_LSM6DSM_ACCEL_FS_2G  = 0,    /**< ±2g full scale */
  SL_LSM6DSM_ACCEL_FS_4G  = 2,    /**< ±4g full scale */
  SL_LSM6DSM_ACCEL_FS_8G  = 3,    /**< ±8g full scale */
  SL_LSM6DSM_ACCEL_FS_16G = 1     /**< ±16g full scale */
} sl_lsm6dsm_accel_fs_t;

/***************************************************************************//**
 * @brief Gyroscope full scale options
 ******************************************************************************/
typedef enum {
  SL_LSM6DSM_GYRO_FS_125DPS  = 1, /**< ±125 dps full scale */
  SL_LSM6DSM_GYRO_FS_250DPS  = 0, /**< ±250 dps full scale */
  SL_LSM6DSM_GYRO_FS_500DPS  = 2, /**< ±500 dps full scale */
  SL_LSM6DSM_GYRO_FS_1000DPS = 4, /**< ±1000 dps full scale */
  SL_LSM6DSM_GYRO_FS_2000DPS = 6  /**< ±2000 dps full scale */
} sl_lsm6dsm_gyro_fs_t;

/***************************************************************************//**
 * @brief Output data rate options
 ******************************************************************************/
typedef enum {
  SL_LSM6DSM_ODR_OFF    = 0,      /**< Power down */
  SL_LSM6DSM_ODR_12_5HZ = 1,      /**< 12.5 Hz */
  SL_LSM6DSM_ODR_26HZ   = 2,      /**< 26 Hz */
  SL_LSM6DSM_ODR_52HZ   = 3,      /**< 52 Hz */
  SL_LSM6DSM_ODR_104HZ  = 4,      /**< 104 Hz */
  SL_LSM6DSM_ODR_208HZ  = 5,      /**< 208 Hz */
  SL_LSM6DSM_ODR_416HZ  = 6,      /**< 416 Hz */
  SL_LSM6DSM_ODR_833HZ  = 7,      /**< 833 Hz */
  SL_LSM6DSM_ODR_1666HZ = 8,      /**< 1.66 kHz */
  SL_LSM6DSM_ODR_3333HZ = 9,      /**< 3.33 kHz */
  SL_LSM6DSM_ODR_6666HZ = 10      /**< 6.66 kHz */
} sl_lsm6dsm_odr_t;

/***************************************************************************//**
 * @brief 3-axis sensor data structure
 ******************************************************************************/
typedef struct {
  float x;  /**< X-axis value */
  float y;  /**< Y-axis value */
  float z;  /**< Z-axis value */
} sl_lsm6dsm_data_t;

/***************************************************************************//**
 * @brief Initialize the LSM6DSM sensor
 *
 * @param[in] config
 *   Pointer to configuration structure containing SPI handle and CS pin
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note This function:
 *   - Initializes SPI communication
 *   - Verifies device ID
 *   - Performs software reset
 *   - Sets default configuration (power down mode)
 ******************************************************************************/
sl_status_t sl_lsm6dsm_init(const sl_lsm6dsm_config_t *config);

/***************************************************************************//**
 * @brief Deinitialize the LSM6DSM sensor
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note Powers down the sensor and releases resources
 ******************************************************************************/
sl_status_t sl_lsm6dsm_deinit(void);

/***************************************************************************//**
 * @brief Configure the sensor sampling rate
 *
 * @param[in] accel_odr
 *   Accelerometer output data rate
 *
 * @param[in] gyro_odr
 *   Gyroscope output data rate
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note This function enables both accelerometer and gyroscope with the
 *       specified data rates. Use SL_LSM6DSM_ODR_OFF to disable a sensor.
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_sample_rate(sl_lsm6dsm_odr_t accel_odr,
                                       sl_lsm6dsm_odr_t gyro_odr);

/***************************************************************************//**
 * @brief Set accelerometer full scale range
 *
 * @param[in] fs
 *   Full scale range selection
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_accel_full_scale(sl_lsm6dsm_accel_fs_t fs);

/***************************************************************************//**
 * @brief Set gyroscope full scale range
 *
 * @param[in] fs
 *   Full scale range selection
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_gyro_full_scale(sl_lsm6dsm_gyro_fs_t fs);

/***************************************************************************//**
 * @brief Check if new accelerometer data is available
 *
 * @return
 *   true if new data is ready, false otherwise
 ******************************************************************************/
bool sl_lsm6dsm_is_accel_data_ready(void);

/***************************************************************************//**
 * @brief Check if new gyroscope data is available
 *
 * @return
 *   true if new data is ready, false otherwise
 ******************************************************************************/
bool sl_lsm6dsm_is_gyro_data_ready(void);

/***************************************************************************//**
 * @brief Read accelerometer data
 *
 * @param[out] data
 *   Pointer to structure to store acceleration data in mg (milligravity)
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note Values are in mg (milligravity): 1000 mg = 1 g = 9.81 m/s²
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_acceleration(sl_lsm6dsm_data_t *data);

/***************************************************************************//**
 * @brief Read gyroscope data
 *
 * @param[out] data
 *   Pointer to structure to store gyroscope data in mdps (millidegrees/sec)
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note Values are in mdps (millidegrees per second): 1000 mdps = 1 dps
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_gyro(sl_lsm6dsm_data_t *data);

/***************************************************************************//**
 * @brief Read accelerometer data (raw 16-bit values)
 *
 * @param[out] x
 *   Pointer to store X-axis raw value
 *
 * @param[out] y
 *   Pointer to store Y-axis raw value
 *
 * @param[out] z
 *   Pointer to store Z-axis raw value
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_acceleration_raw(int16_t *x, int16_t *y, int16_t *z);

/***************************************************************************//**
 * @brief Read gyroscope data (raw 16-bit values)
 *
 * @param[out] x
 *   Pointer to store X-axis raw value
 *
 * @param[out] y
 *   Pointer to store Y-axis raw value
 *
 * @param[out] z
 *   Pointer to store Z-axis raw value
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_gyro_raw(int16_t *x, int16_t *y, int16_t *z);

/***************************************************************************//**
 * @brief Read device ID (WHO_AM_I register)
 *
 * @param[out] device_id
 *   Pointer to store device ID (should be 0x6A for LSM6DSM)
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 ******************************************************************************/
sl_status_t sl_lsm6dsm_get_device_id(uint8_t *device_id);

/***************************************************************************//**
 * @brief Perform software reset
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note This function resets all sensor registers to default values
 ******************************************************************************/
sl_status_t sl_lsm6dsm_reset(void);

/***************************************************************************//**
 * @brief Enable or disable Block Data Update
 *
 * @param[in] enable
 *   true to enable BDU, false to disable
 *
 * @return
 *   @ref SL_STATUS_OK on success, error code otherwise
 *
 * @note When enabled, output registers are not updated until both MSB and LSB
 *       have been read. This prevents reading MSB and LSB from different samples.
 ******************************************************************************/
sl_status_t sl_lsm6dsm_set_block_data_update(bool enable);

/** @} (end addtogroup lsm6dsm) */

#ifdef __cplusplus
}
#endif

#endif // SL_LSM6DSM_H
