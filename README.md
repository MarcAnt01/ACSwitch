# Advanced Charging Switch

[Details](module/README.md)

## Requirements

1. Android NDK r19 or up
2. `zip` binary in PATH

## Building

Building is officially supported on Linux only and tested on Ubuntu 18.10 Desktop
with Android NDK r19c. Building on other platforms though is possible with minor
modifications to build scripts. To build ACSwitch,

1. Export NDK path to `ANDROID_NDK_HOME` environment variable
2. Run `build.sh` script in root of ACSwitch project folder

The build process will patch source files with control files database, compile acs
binaries and pack a flashable zip out of module source tree. Resulting zip will be
in `out/` folder and errors, if any, will be logged in `out/build.log` file.

## Legal

Copyright (c) 2019 Jaymin Suthar. All rights reserved.

See file NOTICE in project root for licensing information and more details.
