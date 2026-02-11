# SimpleFOC BRD4186C port
This repository contains a hardware abstraction layer (HAL) port of the SimpleFOC motor control library for Silicon Labs SDK (SiSDK), with specific support for the BRD4186C radio board.

4 examples are included:
- Open-loop velocity 6PWM
- Hall-sensor velocity 6PWM
- Torque velocity 6PWM (current sense)
- Sensorless velocity 6PWM

The examples can be selected in the device_config.h file with the modification of the **APPLICATION_EXAMPLE** define.
*Note: The **EXAMPLE_CUSTOM** option lets the user create their own example using the motor_control.cpp as the base file.*
