/***************************************************************************//**
 * @file
 * @brief Motor control header
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

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <app-common/zap-generated/cluster-objects.h>

/***************************************************************************//**
 * Initialize motor control
 ******************************************************************************/
void motor_control_init(void);

/***************************************************************************//**
 * Give command to motor
 ******************************************************************************/
void command_the_motor(uint8_t percent, chip::app::Clusters::FanControl::AirflowDirectionEnum direction);

#endif  // MOTOR_CONTROL_H
