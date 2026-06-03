# Motor Control Framework — Current Control Example

Runs closed-loop **velocity control** on a 3-phase BLDC motor using SimpleFOC
Field-Oriented Control (FOC) with **Hall position feedback** and **low-side
current sensing**.

## What it does

- Drives the motor through a 6-PWM gate driver (BOOSTXL-DRV8305)
- Reads rotor angle from three Hall sensors
- Measures phase currents and regulates torque in the `foc_current` mode
- Tracks a velocity setpoint with an outer velocity loop and inner d/q current loops
- Accepts runtime commands over RTT serial (`Commander`) and, when enabled, BLE

The control loop runs at 5 kHz on a dedicated FreeRTOS task; velocity updates
are downsampled to 1 kHz.

## Hardware

| Item | Notes |
|------|-------|
| Radio board | BRD4186C or BRD4401C (pre-filled pin map when selected in the wizard) |
| Motor driver | TI BOOSTXL-DRV8305 BoosterPack |
| Motor | 3-phase BLDC with Hall sensors |
| Power | 24 V supply for the motor stage (adjust limits in `motor_control.cpp` if needed) |

PWM, Hall, and current-sense pins are defined in
`config/motor_control_framework_config.h`. When you create the project for a
supported board, that file is filled automatically from the board overlay
(see `motor_control_framework/overlays/README.md`).

## Getting started

1. Create this example in Simplicity Studio and select your radio board.
2. Connect the radio board to the DRV8305 BoosterPack and wire the motor.
3. Build, flash, and open an RTT terminal.
4. After *Motor ready!* appears, send a velocity target in rad/s, for example:

   ```
   M30
   ```

   Use the `M` prefix followed by the target value (SimpleFOC `Commander` syntax).

## Customization

- **Motor parameters** — pole pairs, resistance, inductance, KV: Configuration
  Wizard on `motor_control_framework_config.h`
- **Control tuning** — PID gains and limits: `motor_control.cpp`
- **BLE interface** — set `ENABLE_BLE` to `1` in the config header

## Key source files

| File | Role |
|------|------|
| `motor_control.cpp` | FOC setup, driver/sensor/current-sense init, control tasks |
| `motor_control_framework_config.h` | Pin map and motor/driver parameters |
| `ble_handler.cpp` | BLE GATT interface (when `ENABLE_BLE` is enabled) |
