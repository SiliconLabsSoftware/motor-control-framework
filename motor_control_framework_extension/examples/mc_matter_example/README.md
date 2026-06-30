# Matter EFR32 Fan Control Example with Motor Control

This project is based on the EFR32 Fan Control example which provides a baseline demonstration of a Fan control
device, built using Matter and the Silicon Labs Simplicity SDK. It can be controlled by
a Matter controller over OpenThread network.

The example is extended with the Simple FOC motor controller Arduino library, however the Matter is not implemented with the Arduino Matter Library.

## Building the example

Clone the repository to a folder, then open it with Simplicity Studio 6.
The solution can be built using Visual Studio Code, alternatively you can change the toolchain.

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

![QR Code](qr_code_img.png)

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
