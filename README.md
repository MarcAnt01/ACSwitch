###### Advanced Charging Switch

###### Copyright (c) 2019 Jaymin Suthar. All rights reserved.

* [Details](https://github.com/sjayminsgithub/ACSwitch-module/blob/master/README.md)

## Notes

* Compilation has been tested on only Ubuntu 18.10 Desktop and build scripts are
  provided only for Linux officially. Mac users might need some patches to work
  correctly and Windows users need to convert paths to their WSL equivalents.

* Build script builds acs binary for API level 21 by default. Though there is no
  API-specific implementation in native part, you might target different levels
  to achieve performance, bugfixes or even smaller binary sizes.

* Build scripts only support NDK r19 or newer due to toolchain path changes.

* Remember that if you had made any changes to original sources, make sure your
  changes are sane as build scripts won't catch any errors your changes gave and
  also update version and versionCode in module.prop.

* If you're going to use this work in other projects or redistribute this work
  with some patches added, please consider making a pull request here first. You
  are also expected to rename your distribution to distinguish both projects.

## Compilation

* Download latest stable Android NDK and export its path to ANDROID_NDK_HOME env
  variable, i.e., `export ANDROID_NDK_HOME=/path/to/android/ndk`

* Make sure you have `zip` available in your PATH, i.e., `sudo apt install zip`

* Build ACSwitch by calling `./build.sh`. This script is a wrapper script which
  will call other scripts to patch source files, compile acc binaries and pack a
  flashable zip out of it. If you need just the binaries, get them out of it.

## Legal

* See file NOTICE in project root for licensing information and more details.
