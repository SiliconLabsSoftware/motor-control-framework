# Motor Control Framework — Sensorless Example

Runs closed-loop **velocity control** on a 3-phase BLDC motor without Hall
sensors or an encoder. Rotor position is estimated by an **MXLEMMING observer**
using phase current measurements.

## What it does

- Drives the motor through a 6-PWM gate driver (BOOSTXL-DRV8305)
- Measures phase currents via low-side shunt amplifiers
- Estimates rotor angle and speed with the MXLEMMING observer
- Starts in open loop, ramps to a minimum speed, then switches to closed-loop
  velocity control automatically
- Accepts runtime commands over RTT serial (`Commander`) and, when enabled, BLE

Startup follows a four-state sequence visible on the RTT console:
`INIT` → `RAMP` → `LOCK` → `CLOSED`. After `CLOSED`, velocity targets from
Commander take effect.

The FOC loop runs at 5 kHz on a dedicated FreeRTOS task; the state machine and
velocity updates run at 1 kHz.

## Hardware

| Item | Notes |
|------|-------|
| Radio board | BRD4186C or BRD4401C (pre-filled pin map when selected in the wizard) |
| Motor driver | TI BOOSTXL-DRV8305 BoosterPack |
| Motor | 3-phase BLDC (no rotor sensor required) |
| Power | 24 V supply for the motor stage (adjust limits in `motor_control.cpp` if needed) |

PWM and current-sense pins are defined in
`config/motor_control_framework_config.h`. Motor electrical parameters
(resistance, inductance, KV) must match your motor for reliable observer
operation. When you create the project for a supported board, the pin map is
filled automatically from the board overlay
(see `motor_control_framework/overlays/README.md`).

## Getting started

1. Create this example in Simplicity Studio and select your radio board.
2. Connect the radio board to the DRV8305 BoosterPack and wire the motor.
3. Verify motor parameters in `motor_control_framework_config.h`.
4. Build, flash, and open an RTT terminal.
5. Watch the startup sequence (`RAMP` → `LOCK` → `CLOSED`). Once closed-loop
   control is active, send a velocity target in rad/s, for example:

   ```
   M30
   ```

   Use the `M` prefix followed by the target value (SimpleFOC `Commander` syntax).

## Customization

- **Motor parameters** — pole pairs, resistance, inductance, KV: Configuration
  Wizard on `motor_control_framework_config.h` (critical for observer accuracy)
- **Startup tuning** — ramp acceleration, lock speed, lock duration:
  `motor_control.cpp`
- **Control tuning** — PID gains and current limit: `motor_control.cpp`
- **BLE interface** — set `ENABLE_BLE` to `1` in the config header

## Key source files

| File | Role |
|------|------|
| `motor_control.cpp` | Observer setup, startup state machine, control tasks |
| `motor_control_framework_config.h` | Pin map and motor/driver parameters |
| `ble_handler.cpp` | BLE GATT interface (when `ENABLE_BLE` is enabled) |
