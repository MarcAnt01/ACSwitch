###### Advanced Charging Switch

###### Copyright (c) 2019 Jaymin Suthar. All rights reserved.

* [Details](https://github.com/sjaymin1001/ACSwitch-module/blob/master/README.md)

## Notes

* Compilation has been tested only on Ubuntu 18.10 Desktop and build scripts are
  provided only for Linux officially, Mac and Windows users might need to modify
  them to build on those respective platforms.

* Build scripts build acs binary for API level 21 by default, but you can target
  different API levels by simply setting `API_LEVEL` in build.sh as there are no
  API-specific implementations in native part.

* Build scripts only support NDK r19 or newer due to toolchain path changes.

## Building

- Download latest stable Android NDK and export its path to ANDROID_NDK_HOME env
  variable, i.e., `export ANDROID_NDK_HOME=/path/to/android/ndk`

- Make sure you have `zip` available in your PATH, i.e., `sudo apt install zip`

- Commit your modifications as the cleanup will hard reset all repos to the last
  commit (please don't mind it, I personally need this feature).

- Run `./build.sh`, this is a wrapper script around other scripts that may patch
  source files, compile acs binaries and pack a recovery flashable zip from 'em.
  If you need just the binaries, extract them out of it.

- The resulting zip will be saved in out/ folder along with build.log containing
  build errors (if any), always check that file prior to use/deploying the zip.

## Legal

* See file NOTICE in project root for licensing information and more details.
