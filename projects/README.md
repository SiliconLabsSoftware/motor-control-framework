# Projects

This directory contains the firmware and shared source for SimpleFOC on Silicon Labs parts. New boards are added as additional top-level directories.

## Directory tree

```
projects/
├── common/
│   ├── arduino_layer/
│   │   ├── generic/
│   │   │   └── api/
│   │   └── specific/
│   ├── ble_stream_adapter/
│   └── simple_foc_platform_specific/
│       ├── MXLEMMING_observer/
│       ├── current_sense/
│       └── driver/
├── external/
│   └── simplefoc/
├── simplefoc-port-brd4186c/
│   ├── device_config.h
│   ├── motor_control.cpp
│   └── example/
├── simplefoc-port-brd4401c/
│   ├── device_config.h
│   ├── motor_control.cpp
│   └── example/
└── simplefoc-port-thingplusmatter/
    ├── device_config.h
    ├── motor_control.cpp
    └── example/
```

## Reference

- **`common/`** — Code shared by all product ports.
- **`arduino_layer/`** — Maps a subset of the Arduino API onto the Silicon Labs SDK.
- **`generic/`** — Portable Arduino layer implementation and headers.
- **`api/`** — Core Arduino-style API headers and utilities under `generic/`.
- **`specific/`** — Board pin map, startup, and peripheral wiring for a target.
- **`ble_stream_adapter/`** — Buffered `Stream` from BLE GATT to the SimpleFOC `Commander` (BLE stack is in the app).
- **`simple_foc_platform_specific/`** — EFR32 motor, observer, and sensing code for SimpleFOC.
- **`MXLEMMING_observer/`** — MXLEMMING-based angle and velocity for sensorless use.
- **`current_sense/`** — In-phase current measurement for FOC.
- **`driver/`** — PWM, timers, and low-level drive for the motor phases.
- **`external/simplefoc/`** — [SimpleFOC](https://github.com/simplefoc/Arduino-FOC) vendored into the repository.
- **`simplefoc-port-brd4186c/`** — SimpleFOC port and examples for the BRD4186C (EFR32xG24).
- **`simplefoc-port-brd4401c/`** — SimpleFOC port and examples for the BRD4401C.
- **`simplefoc-port-thingplusmatter/`** — SimpleFOC port and examples for the SparkFun Thing Plus Matter (MGM240P).
- **`device_config.h`** (in each `simplefoc-port-*`) — Compile-time options, including which example the build uses.
- **`motor_control.cpp`** (in each `simplefoc-port-*`) — Application template for motor setup, FOC wiring, and custom examples (`EXAMPLE_CUSTOM`).
- **`example/`** (in each `simplefoc-port-*`) — Per-demo sources (e.g. open loop, sensorless) selected from `device_config.h`.

More details (wiring, demos) can be found in each port’s `readme.md`.
