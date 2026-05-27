# Motor Control Framework — Open Loop Example

Spins a 3-phase BLDC motor in **open-loop velocity mode** — no position sensor
or current feedback required. Useful as a first bring-up step to verify PWM
output and motor wiring before moving to closed-loop control.

## What it does

- Drives the motor through a 6-PWM gate driver (BOOSTXL-DRV8305)
- Applies a fixed voltage vector that rotates at the commanded speed
- Accepts runtime velocity commands over RTT serial (`Commander`) and, when
  enabled, BLE

The control loop runs in a single FreeRTOS task at ~1 kHz. No FOC alignment or
sensor calibration is needed.

## Hardware

| Item | Notes |
|------|-------|
| Radio board | BRD4186C or BRD4401C (pre-filled pin map when selected in the wizard) |
| Motor driver | TI BOOSTXL-DRV8305 BoosterPack |
| Motor | 3-phase BLDC (Hall sensors not required) |
| Power | 24 V supply for the motor stage (adjust limits in `motor_control.cpp` if needed) |

Only PWM and enable pins are used. Pin assignments live in
`config/motor_control_framework_config.h` and are filled automatically when
you select a supported board (see `motor_control_framework/overlays/README.md`).

## Getting started

1. Create this example in Simplicity Studio and select your radio board.
2. Connect the radio board to the DRV8305 BoosterPack and wire the motor.
3. Build, flash, and open an RTT terminal.
4. After *Motor ready!* appears, send a velocity target in rad/s, for example:

   ```
   M10
   ```

   Use the `M` prefix followed by the target value (SimpleFOC `Commander` syntax).
   Start with a low value — open-loop control uses a conservative voltage limit.

## Customization

- **Motor parameters** — pole pairs: Configuration Wizard on
  `motor_control_framework_config.h`
- **Voltage and speed limits** — `motor_control.cpp`
- **BLE interface** — set `ENABLE_BLE` to `1` in the config header

## Key source files

| File | Role |
|------|------|
| `motor_control.cpp` | Driver init, open-loop control loop, Commander |
| `motor_control_framework_config.h` | Pin map and motor parameters |
| `ble_handler.cpp` | BLE GATT interface (when `ENABLE_BLE` is enabled) |
