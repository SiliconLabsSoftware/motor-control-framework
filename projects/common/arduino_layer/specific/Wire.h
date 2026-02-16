/*
   Wire.h stub file for Arduino compatibility, does not implement actual functionality.
 */
#ifndef WIRE_H
#define WIRE_H

#include "Arduino.h"

class TwoWire {
public:
  void begin();
  void beginTransmission(uint8_t address);
  size_t write(uint8_t data);
  uint8_t endTransmission(bool stop = true);
  size_t requestFrom(uint8_t address, size_t quantity, bool stop = true);
  int read();
};

extern TwoWire Wire;

#endif
