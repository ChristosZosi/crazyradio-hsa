# Crazyradio-HSA

The Crazyradio-HSA is a project created to take the role of the [Crazyradio PA](https://www.bitcraze.io/products/crazyradio-pa/) from [Bitcraze AB](https://www.bitcraze.io/) for decentralized communication with the [Crazyflies 2.1](https://www.bitcraze.io/products/crazyflie-2-1/).

It has its origins in the [Cooperative Control Lab](https://www.hs-augsburg.de/en/Mechanical-and-Process-Engineering/Cooperative-Control-Lab/Cooperative-Control-Lab-3.html) of the [University of Applied Sciences Augsburg](https://www.hs-augsburg.de/en/). There it was first designed for a swarm of Crazyflies to be able to communicate with each other and also with a base station, so they can plan their respective paths to an arbitrary position in cooperation with each other.

This project is now a complete rework of the original one with additional features. At the moment it has two ports, one for the [nRF51 DK](https://www.nordicsemi.com/Products/Development-hardware/nrf51-dk) and one for the [nRF52 DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk).

It features:

* an interface for communication with the [cflib](https://github.com/bitcraze/crazyflie-lib-python) based on the [syslink protocol](https://www.bitcraze.io/documentation/repository/crazyflie2-nrf-firmware/master/protocols/syslink/) via the serial port
* the CrazeT protocol for decentralized communication via Radio 2.4GHz with the Crazyflies (TODO: link the CrazeT documentation)
* a debugging console based on the [J-Link RTT](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) for controlling and debugging the Crazyradio-HSA firmware
* a command handler interface for testing and controlling the Crazyradio-HSA firmware

# Crazyradio-HSA firmware

This repository contains the source code and the project configurations of the firmware. The Crazyradio-HSA uses the [nrfx](https://github.com/NordicSemiconductor/nrfx) library for deploying and configuring the hardware of the nRF5-Series SoCs. I choose deliberately to use the nrfx-library instead of the [nRF5 SDK](https://www.nordicsemi.com/Products/Development-software/nrf5-sdk), as one otherwise would expect, because it is simpler to work with and it is not as bloated as the SDK. Although, I added manually some required sources from the SDK.

## Sources structure

```
├───crazyradio-hsa-nRF51822  eclipse project of the Crazyradio-HSA for nRF51822
├───crazyradio-hsa-nRF52840  eclipse project of the Crazyradio-HSA for nRF52840
├───libs                     library sources
│   ├───boards                 DK board specific sources
|   ├───CrazeT                 source code of the CrazeT protocol
│   ├───nrfx                   nrfx library
│   ├───SEGGER_RTT             SEGGER_RTT sources
│   └───toolchain              toolchain sources
└───src
    ├───arch                 architecture
    ├───board                board hardware (i.e LEDs, buttons etc.)
    ├───config               configuration
    │   ├───nRF51822
    │   └───nRF52840
    ├───debug                debugging console
    └───runtime              runtime sources
```

## Cloning the repository

1. <pre><code> git clone https://github.com/ChristosZosi/crazyradio-hsa.git </code></pre>
2. <pre><code> git submodule update --init </code></pre>

# Hardware

As already mentioned at the moment there are two ports of the Crazyradio-HSA firmware. This means that one can build the firmware and either deploy it on the nRF51822 DK or nRF52840 DK. Eventually other ports could be added i.e. for the [nRF5 dongles](https://www.nordicsemi.com/Products/Development-hardware/nrf51-dongle).

## nRF51822 DK

* 32-bit ARM Cortex M0 processor @16MHz
* 256kB flash and 32kB RAM
* SEGGER J-Link OB Debugger
* Buttons and LEDs for user interaction
* 2.4GHz Transceiver

## nRF52840 DK

* Cortex-M4 with FPU @64 MHz
* 1 MB Flash, 256 KB RAM
* SEGGER J-Link OB Debugger
* Buttons and LEDs for user interaction
* 2.4 GHz Transceiver

# Build and Flash

At the moment I just use the [Eclipse CDT IDE](https://www.eclipse.org/) to configure, build and flash the firmware.

## Tools installation

1. Eclipse
    * Download Eclipse from https://www.eclipse.org/downloads/
    * Install the Eclipse IDE for Embedded C/C++ Developers
2. Install the [GNU Make](https://www.gnu.org/software/make/) to build the sources
3. Install the [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm) for compilation and linking
4. Install the [SEGGER J-Link](https://www.segger.com/downloads/jlink/) for debugging, flashing and using the debugging console, as well as the command handler interface, of the Crazyradio-HSA firmware

## Eclipse projects

1. Open Eclipse IDE
2. Create a new workspace, ideally not in the same path as the repository
3. Import the Crazyradio-HSA projects
    * `File->Import...->Git->Project from Git->next->Existing local repository`
    * `next->Add->Browse->PATH_TO_THIS_REPOSITORY->add->next->Import existing Eclipse projects`
    * `next->CHOSE_THE_PROJECT->finish`

## Build

1. `Project Explorer->Build Targets->DOUBLE_CLICK_ON_TARGET`
    * `all` -> builds alls the sources
    * `clean` -> cleans the build sources
    * `all -j8` -> builds alls the sources in with multiple jobs
    * `soft_clean` -> cleans only the sources in the src-directory

## Debugging and Flashing

1. `Run->Debug Configurations</code></pre>`
2. Double click on `GDB SEGGER J-Link Debugging`
3. In `Main` set the `Project` and `C/C++ Application`
4. In `Debugger`
    * set `Device name`
        * either "nRF51822_xxAC"
        * or "nRF52840_xxAA"
    * set `USB serial or IP name/address`
        * It is the serial number of the debugger. On the nRF5-DKs it can be found on the chip.
5. Now press `Debug` and Happy Debugging. This also flashes the firmware on the SoC.

# License
The actual firmware is licensed under the [MIT License](https://opensource.org/licenses/MIT). The libraries and sources added from elsewhere have their respective licenses on their headers.
