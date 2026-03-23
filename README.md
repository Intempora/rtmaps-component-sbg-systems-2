# Introduction

This repository contains sample RTMaps components that support the [SBG Systems](https://github.com/SBG-Systems/sbgECom)
library to interface SBG Systems devices (IMU, AHRS and INS).

See them in action with the YouTube videos here below:

[![IMAGE_ALT](https://img.youtube.com/vi/4wYnk9i7XWE/0.jpg)]([https://www.youtube.com/watch?v=UmX4kyB2wfg](https://youtu.be/4wYnk9i7XWE))
[![IMAGE_ALT](https://img.youtube.com/vi/zvZJ1cTgCYE/0.jpg)]([https://www.youtube.com/watch?v=zvZJ1cTgCYE](https://youtu.be/zvZJ1cTgCYE))


# Contents

* `sbg_systems_2.u/`
    * `README.md`: This file
    * `CMakeLists.txt`: Cross platform build configuration to build the example. See [this](https://support.intempora.com/hc/en-us/articles/360021738293) for more details on using CMake with the RTMaps SDK
    * `rtmaps_sbg_systems_2.pckinfo`: General information about the package, including the version number
    * `local_interfaces/`: C++ headers
    * `src/`: C++ sources
        * `maps_ellipse_device`: Component handling the connection to an SBG device
        * `maps_ellipse_decoder`: Component extracting useful information from the device connection


# Prerequisites

To build and use the RTMaps components in this repository, you will need the following:
* A Windows or Linux PC. The RTMaps components have been tested on Windows 11 and Ubuntu 22.04. Virtual machines might not be supported.
* An installation of RTMaps, containing the RTMaps SDK.
* The [SBGEcom C++ library](https://github.com/SBG-Systems/sbgECom). Follow the instructions on the SBGEcom repository, or [below](#installing-the-sbgecom-library).
* A C++ compiler:
    * In Linux, you can install one with the command `sudo apt install build-essential`.
    * In Windows, Microsoft Visual C++ is required. These components have been tested with Visual C++ 17 2022.
    * For more details, see [C++ Compiler prerequisite](https://support.intempora.com/hc/en-us/articles/360021738293#c-compiler).
* CMake.

## Installing the SBGEcom library
* Download the sources [here](https://github.com/SBG-Systems/sbgECom). 
* Move into the folder containing the root _CMakeLists.txt_ file.
* Build library:
```sh
cmake -B build-dir                              # Generate build files in build-dir
```
```sh
cmake --build build-dir -j 10 --config Release  # Build library
```
* Install library (requires administrator rights):
```sh
cmake --install build-dir
```

# Building
This sample builds using CMake. Please follow the instructions on [Developing RTMaps Components Using CMake](https://support.intempora.com/hc/en-us/articles/360021738293) for more information.
* Make sure your environment variables contain RTMAPS_SDKDIR set to the installation folder of RTMaps on your machine
* Download the sources from this repository
* Move into the root folder (the folder that contains the root _CMakeLists.txt_ file and this _README.md_ file)
## Windows
```sh
cmake -B build -G "Visual Studio 17 2022"
```
```sh
cmake --build build -j 10 --config Release
```
## Linux
```sh
cmake -B build -G "Unix Makefiles"
```
```sh
cmake --build build -j 10 --config Release
```
This will generate a package file _sbg_systems_2.pck_ in the build directory. The complete path will be logged during
the build.

# Using the package
## Installing the package (optional)
You can install the package to make it available system-wide. This requires administrator rights.
```sh
cmake --install build
```
This will install the package in the default RTMaps package directory (`[RTMAPS_SDKDIR]/packages`). This also installs
the documentation files used by RTMaps Studio to display help.

## RTMaps Studio
* Open RTMaps Studio
* In the Explorer view, select the folder containing the _sbg_systems_2.pck_ file generated
* Double-click on _sbg_systems_2.pck_ to load the package
* Now the package is loaded and you can drag and drop components from the Components view into the Diagram view

## RTMaps Runtime
* Run RTMaps Runtime
* Load the diagram
```
register <</path/to/sbg_systems_2.pck>>
```
* You can now create the components
```
ellipse_device MyDevice
ellipse_decoder MyDecoder
```
