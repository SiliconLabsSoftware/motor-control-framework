**Copyright 2025 Silicon Laboratories Inc. [https://www.silabs.com](https://www.silabs.com/)**

SPDX-License-Identifier: LicenseRef-MSLA

## License

The default license for this repository is the Silicon Labs [Master Software License Agreement (MSLA)](https://www.silabs.com/about-us/legal/master-software-license-agreement), unless a file or third-party component contains a different license notice. When a file or component contains its own license notice, that notice governs that file or component. Nothing in the MSLA is intended to limit rights granted under those third-party open-source licenses.

This repository uses third-party open-source software:

- **ArduinoCore-API**  
  Licensed under the GNU Lesser General Public License version 2.1.  
  Used as an unmodified Git submodule.  
  Source: https://github.com/arduino/ArduinoCore-API  
  Local path: `motor_control_framework_extension/motor_control_framework/external/ArduinoCore-API`  
  License text: `motor_control_framework_extension/motor_control_framework/external/ArduinoCore-API/LICENSE`

- **SimpleFOC / Arduino-FOC**  
  Licensed under the MIT License.  
  Used as an unmodified Git submodule.  
  Source: https://github.com/simplefoc/Arduino-FOC  
  Local path: `motor_control_framework_extension/motor_control_framework/external/simplefoc`  
  License text: `motor_control_framework_extension/motor_control_framework/external/simplefoc/LICENSE`

- **Silicon Labs Arduino Core derived files**  
  Some Arduino compatibility-layer files were derived from the Silicon Labs Arduino Core and retain their file-level MIT license notices.  
  Source: https://github.com/SiliconLabsSoftware/arduino

- **`overloads.h`**  
  `motor_control_framework_extension/motor_control_framework/common/arduino_layer/generic/overloads.h` contains its own LGPL v2.1-or-later license notice. That file remains governed by the license stated in its header.

- **MXLEMMING observer**  
  The MXLEMMING observer files are derived from Arduino-FOC-drivers and retain their MIT license notices.  
  Source: https://github.com/simplefoc/Arduino-FOC-drivers

The third-party components above are provided under their respective licenses. If this repository is distributed as source code, users should initialize the referenced submodules or obtain the third-party source from the linked upstream repositories. If firmware or other binaries are distributed that include LGPL-covered code, the distributor is responsible for satisfying the applicable LGPL v2.1 requirements.

The full text of the GNU Lesser General Public License version 2.1 is provided in [LGPL-2.1.md](LGPL-2.1.md). It applies to the LGPL-covered components and files identified above, including ArduinoCore-API and `motor_control_framework_extension/motor_control_framework/common/arduino_layer/generic/overloads.h`.
