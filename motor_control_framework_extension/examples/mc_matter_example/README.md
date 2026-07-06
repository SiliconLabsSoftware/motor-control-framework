# Motor Control Framework - Matter Control Example

This project is based on the Matter - Fan Control over Thread example which provides a baseline demonstration of a Fan control
device, built using Matter and the Silicon Labs Simplicity SDK. It can be controlled by
a Matter controller over OpenThread network.

The example is extended with the Simple FOC motor controller Arduino library, however the Matter is not implemented with the Arduino Matter Library.

## Building the example

0. Install the Motor Control Framework Extension in Simplicity Studio 6: [README.md](../../../README.md#2-install-the-extension-in-simplicity-studio-6), and the Matter Extension (using Simplicity Installer)
1. Create this example in Simplicity Studio and select the **BRD4118A** radio
   board so the pin overlay is applied.
2. Connect the radio board to the DRV8305 BoosterPack and wire the motor + Hall
   sensors.
3. Build, flash, and commission according to the **Provision and Control** section

## Fan Control Application User Interface

**LED 0**

Simulates the Fan. The following states are possible:

-   _Solid On_ ; Fan is on
-   _Off_ ; Fan is off

**Push Button 0**

-   _Press and Release_ : Start, or restart, BLE advertisement in fast mode. It will advertise in this mode
for 30 seconds. The device will then switch to a slower interval advertisement.
After 15 minutes, the advertisement stops. In addition, this button should also print the QR Code URL to the RTT logs.

-   _Pressed and hold for 6 s_ : Initiates the factory reset of the device.
 Releasing the button within the 6-second window cancels the factory reset
 procedure. **LEDs** blink in unison when the factory reset procedure is
 initiated.

## Provision and Control

![QR Code](image/qr_code_img.png)

Above QR Code can be used for commissioning with a smartphone, alternatively its URL can be found in the **RTT logs upon startup OR by pressing BTN0**

Note: This QR Code is only valid for an unprovisioned device. Provisioning may change the QR Code.

You can provision and control the Matter device using the python controller, chip-tool (standalone or pre-built), Android, iOS app or the mattertool utility from the Matter Hub package provided by Silicon Labs. The pre-built chip-tool instance ships with the Matter Hub image. More information on using the Matter Hub can be found in the online Matter documentation here: [Silicon Labs Matter Documentation](https://docs.silabs.com/matter/2.8.0/matter-thread/raspi-img)

More information on using the chip-tool directly can be found here: [CHIPTool](https://github.com/project-chip/connectedhomeip/blob/master/examples/chip-tool/README.md)

Here is an example with the CHIPTool:

Pairing with chip-tool:
```shell
chip-tool pairing ble-thread <Node-ID> hex:<operationalDataset> 20202021 3840

chip-tool fancontrol write fan-mode 1 <Node-ID> 1

chip-tool fancontrol read fan-mode <Node-ID> 1

chip-tool fancontrol read fan-mode-sequence <Node-ID> 1
```

## Physical BLDC Fan control

Control of the Fan is achieved using the SimpleFOC Arduino Library.
The motor-control is run hard real-time from an interrupt, while the commands and parameters are set from a separate motor-control task.

### SystemView timestamp resolution (optional, higher-resolution traces)

This example is compatible with the **SEGGER SystemView** component, if you wish to add it after project creation.
By default it is configured to use the **sleeptimer** as its timestamp tick base
(`SEGGER_SYSVIEW_TIMESTAMP_SOURCE_SLEEPTIMER`, set in the project `.slcp`).
The only trade-off is timestamp resolution: SystemView timestamps tick at the sleeptimer frequency
rather than the CPU clock.

If you want **higher-resolution** SystemView logging, switch the timestamp
source to the **DWT cycle counter**, which ticks at `SystemCoreClock`:

1. In Project Configurator (or the project `.slcp` `configuration:` section) set:

   ```
   SEGGER_SYSVIEW_TIMESTAMP_SOURCE = SEGGER_SYSVIEW_TIMESTAMP_SOURCE_DWT
   ```

2. Add a CMSIS device-header include to the generated
   `config/sl_systemview_config.h`, just inside the include guard, so `DWT` is
   declared when `SEGGER_SYSVIEW.c` is compiled:

   ```c
   #ifndef SL_SYSTEMVIEW_CONFIG_H
   #define SL_SYSTEMVIEW_CONFIG_H

   #include "em_device.h"   // <-- add this line (declares DWT->CYCCNT)
   ```

   Without this include the DWT build fails with
   `error: 'DWT' undeclared ... DWT->CYCCNT`.

This second step can't be automated from the `.slcp`: the `segger_systemview`
component declares `sl_systemview_config.h` **without a `file_id`**, so the
project cannot register a `config_file` override for it (a plain `config_file`
entry collides with the component and fails generation with *"file
sl_systemview_config.h is defined for multiple components"*). Hence it's a
one-time manual edit only needed when opting into the DWT source.
