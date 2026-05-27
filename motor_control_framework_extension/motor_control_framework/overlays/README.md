# Board-specific config overlays

Pre-filled replacements for the framework's base configuration header
[`motor_control_framework/config/motor_control_framework_config.h`](../config/motor_control_framework_config.h).
When a user creates one of the Motor Control Framework examples and selects a
supported radio board, Simplicity Studio copies the matching overlay into the
generated project's `config/motor_control_framework_config.h`.

## Directory layout

```
overlays/
├── README.md
├── brd4186c/
│   └── motor_control_framework_config.h   # BRD4186C (EFR32xG24) pin map
└── brd4401c/
    └── motor_control_framework_config.h   # BRD4401C (EFR32xG28) pin map
```

Each overlay is **board-scoped**, not example-scoped. All four examples share
the same overlay for a given board because the physical wiring is identical
across Open Loop, Hall Sensor, Sensorless, and Current Control.

| Board     | Feature name | Overlay path                                      |
|-----------|--------------|---------------------------------------------------|
| BRD4186C  | `brd4186c`   | `overlays/brd4186c/motor_control_framework_config.h` |
| BRD4401C  | `brd4401c`   | `overlays/brd4401c/motor_control_framework_config.h` |

## How it works

1. The base component
   [`motor_control_framework.slcc`](../../components/motor_control_framework.slcc)
   ships a blank template config with a stable `file_id`:

   ```yaml
   config_file:
     - path: config/motor_control_framework_config.h
       file_id: motor_control_framework_config
   ```

2. Each example `.slcp` declares one **conditional override** per supported
   board. If no condition matches, the blank template from step 1 is used and
   the build fails at the `#error` guard until the user fills in the pins.

   ```yaml
   # in examples/mc_sensorless_example/mc_sensorless_example.slcp
   config_file:
     - override:
         component: motor_control_framework
         file_id: motor_control_framework_config
       path: ../../motor_control_framework/overlays/brd4186c/motor_control_framework_config.h
       condition:
         - brd4186c
     - override:
         component: motor_control_framework
         file_id: motor_control_framework_config
       path: ../../motor_control_framework/overlays/brd4401c/motor_control_framework_config.h
       condition:
         - brd4401c
   ```

   The same `config_file:` block appears in all four example projects:

   - `examples/mc_open_loop_example/mc_open_loop_example.slcp`
   - `examples/mc_hall_sensor_example/mc_hall_sensor_example.slcp`
   - `examples/mc_sensorless_example/mc_sensorless_example.slcp`
   - `examples/mc_current_control_example/mc_current_control_example.slcp`

3. When the user picks **BRD4186C** in the project wizard, SS6 satisfies the
   `brd4186c` condition and copies that overlay header into the project. Same
   for **BRD4401C** with `brd4401c`. Any other board keeps the blank template.

## Overlay contents

Each board overlay pre-fills:

- **Runtime options** — `ENABLE_MONITOR`, `ENABLE_BLE`
- **Motor parameters** — pole pairs, resistance, KV, inductance
- **Current sense front-end** — shunt resistance and amplifier gain
- **Pin map** — full BRD4186C / BRD4401C wiring (PWM, Hall, current sense, SPI)

## Adding a new board overlay

1. Create `overlays/<board-feature>/motor_control_framework_config.h`
   (copy the nearest existing overlay and adjust the configuration to match the board).
2. Add a conditional `config_file:` override to **each** of the four example
   `.slcp` files:

   ```yaml
     - override:
         component: motor_control_framework
         file_id: motor_control_framework_config
       path: ../../motor_control_framework/overlays/<board-feature>/motor_control_framework_config.h
       condition:
         - <board-feature>
   ```

3. Use the board feature name exactly as declared by the Simplicity SDK board
   component (inspect its `.slcc` if unsure). Known values for the boards
   above: `brd4186c`, `brd4401c`.

No separate `.slcc` overlay component is needed. Overrides must live in the
project `.slcp` itself — SS6 does not apply `config_file:` overrides from
secondary components.

## Conventions

- **Overlay header path:** `overlays/<board-feature>/motor_control_framework_config.h`
- **Path in `.slcp`:** relative to the `.slcp` directory →
  `../../motor_control_framework/overlays/<board-feature>/motor_control_framework_config.h`
- **Condition:** the board feature name from the Simplicity SDK (`brd4186c`,
  `brd4401c`, …).
- **Unused pins:** set to `NA`. The `#error` guard at the
  bottom of the config header fires if any pin is left at `MC_PIN_UNSET`.
