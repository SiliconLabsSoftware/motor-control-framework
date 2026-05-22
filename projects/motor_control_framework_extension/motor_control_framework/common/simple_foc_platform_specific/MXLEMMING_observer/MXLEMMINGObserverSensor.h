/***************************************************************************//**
 * @file MXLEMMINGObserverSensor.h
 * @brief MXLEMMING Observer Sensor header file
 *******************************************************************************
 * # License
 * MIT License
 *
 * Copyright (c) 2021 Richard Unger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/
#ifndef MXLEMMING_OBSERVER_SENSOR_H
#define MXLEMMING_OBSERVER_SENSOR_H

#include "Arduino.h"
#include "FOCMotor.h"
#include "Sensor.h"

/**

 */

class MXLEMMINGObserverSensor: public Sensor
{
public:
  /**
     MXLEMMINGObserverSensor class constructor
     @param m  Motor that the MXLEMMINGObserverSensor will be linked to
   */
  MXLEMMINGObserverSensor(const FOCMotor&m);
  void update() override;

  void init() override;

  // Abstract functions of the Sensor class implementation
  /** get current angle (rad) */
  float getSensorAngle() override;

  // For sensors with slow communication, use these to poll less often
  unsigned int sensor_downsample = 0;   // parameter defining the ratio of downsampling for sensor update
  unsigned int sensor_cnt = 0;   // counting variable for downsampling
  float flux_alpha   = 0;   // Flux Alpha
  float flux_beta    = 0;   // Flux Beta
  float flux_linkage = 0;   // Flux linkage, calculated based on KV and pole number
  float i_alpha_prev = 0;   // Previous Alpha current
  float i_beta_prev  = 0;   // Previous Beta current
  float electrical_angle = 0;   // Electrical angle
  float electrical_angle_prev = 0;   // Previous electrical angle
  float angle_track = 0;   // Total Electrical angle

protected:
  const FOCMotor& _motor;
};

#endif
