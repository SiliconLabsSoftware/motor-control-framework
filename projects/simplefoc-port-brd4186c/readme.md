# SimpleFOC BRD4186C port
This repository contains a hardware abstraction layer (HAL) port of the SimpleFOC motor control library for Silicon Labs SDK (SiSDK), with specific support for the BRD4186C radio board.

### Examples
4 examples are included:
- Open-loop velocity 6PWM
- Hall-sensor velocity 6PWM
- Torque velocity 6PWM (current sense)
- Sensorless velocity 6PWM

The examples can be selected in the `device_config.h` file with the modification of the **APPLICATION_EXAMPLE** define.
*Note: The **EXAMPLE_CUSTOM** option lets the user create their own example using the `motor_control.cpp` as the base file.*

### Wiring Table: BRD4186C to BOOSTXL-DRV8305 & BLDC Motor

This table describes the connections between the BRD4186C, the TI BOOSTXL-DRV8305 driver board, and a 3-phase BLDC motor with Hall sensors.

| From (BRD4186C) | To (DRV8305 BoosterPack Pin) | BLDC MOTOR | Function / Description |
| :--- | :--- | :--- | :---|
| `3.3V` | `3V3` | HALL/ENC Supply*  | 3.3V Power; the BoosterPack provides 3.3V through an LDO |
| `GND`  | `PowerSupply GND` | HALL/ENC sensor GND | Common Ground |
| N/A    | `PowerSupply 24V` | N/A | Power supply for power stage 4.4 to 45 V, consider motor power|
| `PA04`   | `ENGATE` | N/A | Enable DRV8305 gate driver |
| `PB00`   | `PWMHA` | N/A | PWM Phase A High-Side Gate Signal |
| `PA08`   | `PWMLA` | N/A | PWM Phase A Low-Side Gate Signal |
| `PA09`   | `PWMHB` | N/A | PWM Phase B High-Side Gate Signal |
| `PB05`   | `PWMLB` | N/A | PWM Phase B Low-Side Gate Signal |
| `PA00`   | `PWMHC` | N/A | PWM Phase C High-Side Gate Signal |
| `PB02`   | `PWMLC` | N/A | PWM Phase C Low-Side Gate Signal |
| `PB04`   | N/A | HALL A or Encoder A | Motor sensor connection (Hall configuration in examples) |
| `PB01`   | N/A | HALL B or Encoder B | Motor sensor connection (Hall configuration in examples) |
| `PB03`   | N/A | HALL C or Encoder Index | Motor sensor connection (Hall configuration in examples) |
| `PC09`   | `ISENA` | N/A | Phase A current sense |
| `PD05`   | `ISENB` | N/A | Phase B current sense |
| `PD04`   | `ISENC` | N/A | Phase C current sense |
| `PC01`   | `SDI`  | N/A | SPI_MOSI (Optional, not mandatory to run examples) |
| `PC06`   | `SDO`  | N/A | SPI_MISO (Optional, not mandatory to run examples) |
| `PC03`   | `SCLK` | N/A | SPI_CLK (Optional, not mandatory to run examples) |
| `PC08`   | `SCS`  | N/A | SPI_CS (Optional, not mandatory to run examples) |
| `PA05`   | `nFAULT` | N/A | Fault indicator, specific FAULT status can be obtained through the status registers |
| `PC02`   | `VSENA` | N/A | Phase A Voltage sense (Optional, not mandatory to run examples) |
| `PC05`   | `VSENB` | N/A | Phase B Voltage sense (Optional, not mandatory to run examples) |
| `PC07`   | `VSENC` | N/A | Phase C Voltage sense (Optional, not mandatory to run examples) |
| `PD02`   | `VSENVPVDD`   | N/A | DC BUS Voltage sense (Optional, not mandatory to run examples)|
| N/A    | `PHASE U` | `PHASE U` | Motor phase connection |
| N/A    | `PHASE V` | `PHASE V` | Motor phase connection |
| N/A    | `PHASE W` | `PHASE W` | Motor phase connection |

**Important Notes:**
*   **Power:** Ensure the DRV8305's `PVDD` and `GVDD` jumpers are correctly set for your motor's voltage. The power supply should be rated at least twice the motor’s nominal power. The BoosterPack can supply the radio board if it is not connected to USB.
* **Rotor sensor:** Some Encoder or Hall sensors might require 5V supply, ensure proper level shifting if required.

---
