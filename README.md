# Advanced Charging Switch

## [Details](https://github.com/Magisk-Modules-Repo/ACSwitch/blob/devel/README.md)

## Requirements

1. Android NDK r19 or newer.
2. `zip` available in PATH.

## Building

Building is supported on Linux only and has been tested on Ubuntu 18.10 Desktop.
Mac environments may need some changes to the scripts and Windows users may need
WSL along with some changes to paths. To build ACSwitch,

1. Export Android NDK path to `ANDROID_NDK_HOME` environment variable.
2. Run `./build.sh` from root of ACSwitch project folder.

The build process will configure source files, compile acs binaries and create a
recovery flashable zip. Output zip will be placed into `out/` folder and stderr,
if any, will be dumped into `out/build.log` file.

## Legal

Copyright (c) 2019 Jaymin Suthar. All rights reserved.
See file NOTICE in project root for licensing information and more details.
