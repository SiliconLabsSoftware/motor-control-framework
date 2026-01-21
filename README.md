# Developer Services template project
This repository contains a hardware abstraction layer (HAL) port of the SimpleFOC motor control library for Silicon Labs SDK (SiSDK), with specific support for the SparkFun Thing Plus Matter MGM240P development board.
## How to use the template
1. Import the [basic ruleset](https://github.com/SiliconLabsSoftware/devs-template/blob/main/.github/rulesets/Silabs-basic-public-ruleset.json). Follow the official GitHub [guide](https://docs.github.com/en/enterprise-cloud@latest/organizations/managing-organization-settings/managing-rulesets-for-repositories-in-your-organization#importing-a-ruleset).
2. Update if necessary the [issue_templates](.github/ISSUE_TEMPLATE/) and the [pull request template](./.github/PULL_REQUEST_TEMPLATE.md)
3. Create your sw projects under [projects/](projects/) folder.
4. Check [.gitignore](.gitignore) file and modify it if it is necessary
5. Check the [./Dockerfile](./Dockerfile) and extend it if necessary
6. Make sure that the whole project can be compiled with a single "make all" command.  
   also implement "make clean"
7. Fill out the [CODEOWNERS](./.github/CODEOWNERS) file. Here is the official github [guide](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-code-owners)
8. Add github app private key for CLA assistant signature. Contact silicon labs github support person for it.
9. Check the available [workflows](./.github/workflows) and adjust them according to the repo types (internal or public)
10. Update this Readme file and remove this list from it.

## Hardware requirements
* **[SparkFun Thing Plus Matter](https://www.sparkfun.com/sparkfun-thing-plus-matter-mgm240p.html)**
* **DRV8305 BoosterPack (BOOSTXL-DRV8305EVM)**
* **BLDC Motor: DF45M024053 – A2**
* USB cable for programming and serial monitor

## Hardware Setup
### SparkFun Thing Plus Matter
A dedicated interface board setup connecting the Motor - Power Stage - SparkFun Thing Plus Matter. Jump wires can be used as well to connect the boards.

![hw_setup](resources/hw_with_thingplusmatter.png)

Connect the SparkFun Thing Plus Matter board to the DRV8305EVM according to the board pin mapping (phase outputs, PWM inputs, and Hall sensor connections).

![MC Wiring](resources/sparkfunthingplusmatter_pinout.png)

### Wiring Table: SparkFun Thing Plus Matter to BOOSTXL-DRV8305 & BLDC Motor

This table describes the connections between the SparkFun Thing Plus Matter, the TI BOOSTXL-DRV8305 driver board, and a 3-phase BLDC motor with Hall sensors.

| From (SparkFun Thing Plus Matter) | To (DRV8305 BoosterPack Pin) | BLDC MOTOR | Function / Description |
| :--- | :--- | :--- | :---|
| `3.3V` | `3V3` | HALL/ENC Supply*  | 3.3V Power; the BoosterPack provides 3.3V through an LDO |
| `GND`  | `PowerSupply GND` | HALL/ENC sensor GND | Common Ground |
| N/A    | `PowerSupply 24V` | N/A | Power supply for power stage 4.4 to 45 V, consider motor power|
| `A0`   | ? | ? | ? |
| `A1`   | ? | ? | ? |
| `A2`   | ? | ? | ? |
| `A3`   | `ISENB` | N/A | Phase B current sense |
| `A4`   | `ISENC` | N/A | Phase C current sense |
| `A5`   | `ISENA` | N/A | Phase A current sense |
| `A6`   | ? | ? | ? |
| `A7`   | ? | ? | ? |
| `A8`   | ? | ? | ? |
| `D0`   | N/A | HALL B or Encoder B | Motor sensor connection (Hall configuration in examples) |
| `D1`   | N/A | N/A | N/A |
| `D2`   | N/A | N/A | N/A |
| `D3`   | N/A | HALL A or Encoder A | Motor sensor connection (Hall configuration in examples) |
| `D4`   | `PWMHA` | N/A | PWM Phase A High-Side Gate Signal |
| `D5`   | `PWMLA` | N/A | PWM Phase A Low-Side Gate Signal |
| `D6`   | `PWMHB` | N/A | PWM Phase B High-Side Gate Signal |
| `D7`   | `PWMLB` | N/A | PWM Phase B Low-Side Gate Signal |
| `D8`   | `PWMHC` | N/A | PWM Phase C High-Side Gate Signal |
| `D9`   | `PWMLC` | N/A | PWM Phase C Low-Side Gate Signal |
| `D10`  | `ENGATE` | N/A | Enable DRV8305 gate driver |
| `D11`  | N/A | HALL C or Encoder Index | Motor sensor connection (Hall configuration in examples) |
| N/A    | `PHASE U` | `PHASE U` | Motor phase connection |
| N/A    | `PHASE V` | `PHASE V` | Motor phase connection |
| N/A    | `PHASE W` | `PHASE W` | Motor phase connection |

**Important Notes:**
*   **Power:** Ensure the DRV8305's `PVDD` and `GVDD` jumpers are correctly set for your motor's voltage. The power supply should be rated at least twice the motor’s nominal power. The BoosterPack can supply the SparkFun Thing Plus Matter if it is not connected to USB.
* **Rotor sensor:** Some Encoder or Hall sensors might require 5V supply, ensure proper level shifting if required.

---

## Build
Build system dependency (these are installed if Simplicity Studio is installed):
 - CMake (v3.25 or newer)
 - Ninja (v1.10 or newer)
 - ARM GCC compiler (v12.2 or newer)
 - Make (optionally to run the utility scripts)

### Build with Make
To build every binary you shall run (in the root folder)
```shell
make
```

The following build targets are available:
 - `all`  
    Builds all firmware components. This is the default target.
 - `simpleFOC-port-mg24`  
    Builds the simpleFOC port firmware for Sparkfun Thing Plus Matter board.
 - `clean`  
    Cleans all build artifacts from firmware components.

The following arguments can be added:
 - `TARGET`  
   Specifies the build operation.  
   Options: `clean_build`, `clean`, `configure`, or `build`.  
    - `clean_build` performs clean, configure, and build in sequence (default).  
    - `build` performs incremental build (requires prior configure step).  
    - `configure` sets up build system without building.  
    - `clean` removes build artifacts.
 - `TYPE`  
   Build configuration type.  
   Options: `Debug` (default) or `Release`.  
   Currently not supported.

Examples:
```shell
make simpleFOC-port-mg24 TARGET=build TYPE=Release
make simpleFOC-port-mg24 TARGET=clean_build
make all
```

### Build with Docker
Dockerfile is also present in the root folder, to use it the following shall be done:
 1. Install Docker: https://docs.docker.com/engine/install/
 2. Build a docker image. (Default platform is x86_64.)  
    `docker build . -t simplefoc-port-mg24-build-env:latest`  
    You can also use the Makefile to do this operation. This can also recognize Apple Silicon (aarch64).  
    `make docker_image`  
 3. Build the image  
    `docker run --rm -v .:/home -w /home simplefoc-port-mg24-build-env:latest /bin/sh -c "make all"`  
    With Makefile:  
    `make docker_build`  

## Flashing of Sparkfun Thing Plus Matter board
Can be flashed on any host with Simplicity Commander (or with any compatible ARM debugger).
Simplicity Commander guide: https://www.silabs.com/documents/public/user-guides/ug162-simplicity-commander-reference-guide.pdf

## Contributing
Please follow the [CONTRIBUTING](./.github/CONTRIBUTING.md) guideline.

## License
See the [LICENSE.md](./LICENSE.md) file for details.
