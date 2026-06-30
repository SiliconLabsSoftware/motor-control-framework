/***************************************************************************//**
 * @file
 * @brief IMU task header
 *******************************************************************************
 * # License
 * <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

 #ifndef IMU_TASK_H
 #define IMU_TASK_H

/***************************************************************************//**
 * Initialize IMU task
 ******************************************************************************/
void imu_task_init(void);
void imu_task_deinit(void);
/*****************************************************************************
 * get latest anomaly score
 ******************************************************************************/
float getAnomaly();

 #endif  // IMU_TASK_H
