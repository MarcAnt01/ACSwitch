# Advanced Charging Switch

* [Details](https://github.com/sjaymin1001/ACSwitch-module/blob/master/README.md)

## Notes

* Build scripts are provided for Linux only and building has been tested only on
  Ubuntu 18.10 Desktop, if you use a Mac or a Windows environment, you can build
  ACSwitch with some little modifications to scripts.

* Build scripts only support NDK r19 or newer due to toolchain path changes.

## Building

- Download latest stable Android NDK and export its path to ANDROID_NDK_HOME env
  variable, i.e., `export ANDROID_NDK_HOME=/path/to/android/ndk`

- Make sure you have `zip` available in your PATH, i.e., `sudo apt install zip`

- Commit your modifications as the cleanup will hard reset all repos to the last
  commit (please don't mind it, I personally need this feature).

- Run `./build.sh`, this wrapper script will call around other scripts which may
  patch source files, compile acs binaries and pack a recovery flashable zip out
  of them. If you need just the binaries, you can extract them out of the zip.

- The resulting zip will be put into out/ folder along with build.log containing
  build errors (if any), always check those logs prior to use/deploying the zip.

## Legal

* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
* See file NOTICE in project root for licensing information and more details.
