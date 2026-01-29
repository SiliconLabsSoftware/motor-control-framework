/*
   SPI.h stub file for Arduino compatibility, does not implement actual SPI functionality.
 */
#ifndef SPI_H
#define SPI_H

#include "Arduino.h"

// SPI modes
#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

// Bit order
#define MSBFIRST 1
#define LSBFIRST 0

class SPISettings {
public:
  SPISettings() : clock_(1000000), bitOrder_(MSBFIRST), dataMode_(SPI_MODE0) {
  }
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    : clock_(clock), bitOrder_(bitOrder), dataMode_(dataMode) {
  }

  uint32_t clock_;
  uint8_t bitOrder_;
  uint8_t dataMode_;
};

class SPIClass {
public:
  void begin();
  void end();
  uint8_t transfer(uint8_t data);
  uint16_t transfer16(uint16_t data);
  void beginTransaction(SPISettings settings);
  void endTransaction();

  // Transaction support might be needed
  // void beginTransaction(SPISettings settings);
  // void endTransaction();
};

extern SPIClass SPI;

#endif
