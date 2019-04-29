# Advanced Charging Switch

### Basically enables you to switch charging state.

## Description

ACSwitch automatically switches charging off when battery level reaches a certain
disable threshold and back on as soon as level drowns to enable threshold. Thus,
keeping battery level bouncing between those boundaries. This feature is called
'Automation'.

There's one more feature namingly 'method's, which basically helps in enabling or
disabling charging based on conditions including battery level and time. Though
it is recommended only if you really need it or have decent knowledge of how phone
batteries work.

Please see 'Usage' section on manipulating these features and playing with ACSwitch.

## Requirements

1. Android Lollipop or up
2. ARM or x86 based chipset
3. Magisk v18.2 (18105) or up
4. Any root solution and Init.d support

Having either one of 3 or 4 would suffice, 3 is favored if both are detected.

## Downloads

Please obtain release zips [from GitHub releases](https://github.com/Magisk-Modules-Repo/ACSwitch/releases),
downloading from Magisk Manager enforces Magisk framework which forbids some
installation functions.

## Installation

Assured your device meets requirements, ACSwitch can be flashed like any other
flashable, Magisk Manager and TWRP are advised as installation mediums.

## Setup

If you aren't a power-user and don't wanna mess with understanding commandline
(although it's pretty well explained), here is what a minimal setup should be
like,

    su                                    # Obtain a root shell
    acs --configure                       # Configure ACSwitch
    acs --update 70 60                    # Update thresholds, substitute 70 and 60
    acs --daemon launch                   # Launch the daemon

## Usage

`acs [<option> [<args>...]...]`

    [--toggle] <state>

        Toggles Automation on or off.
        <state> can be either 'ON' or 'OFF'.

        -> `acs --toggle ON`  will toggle Automation on
        -> `acs --toggle OFF` will toggle Automation off

    [--update] <thr_disable> <thr_enable>

        Updates Automation disable threshold and enable threshold,
        resets them to defaults if no values were specified.
        <thr_disable> and <thr_enable> must be integers.

        -> `acs --update 90 80` will set disable threshold to 90
                                and enable threshold to 80
        -> `acs --update`       will reset thresholds (70 60)

    [--method] <format_str>

        Run a method based on format string <format_str>.
        Here, format string must follow the pattern:
            (e|d)(%|s|m|h)(threshold: int)

        where...
        ... (e|d)     defines if enabling or disabling charging,
        ... (%|s|m|h) defines if seeking level or time interval,
        ...           and this is the value of threshold.

        -> `acs --method es60` will enable charging for 60 seconds
        -> `acs --method d%40` will disable charging until 40%
        -> `acs --method em30` will enable charging for 30 minutes

    [--configure]

        Configure ACSwitch, device must be charging concurrently.
        This task is required each time you change kernel or
        update ACSwitch.

        -> `acs --configure` will configure ACSwitch

    [--daemon] <action>

        Launches or kills the daemon.
        <action> can be either 'launch' or 'kill'.

        -> `acs --daemon launch` will launch the daemon
        -> `acs --daemon kill`   will kill the daemon

    [--info]

        Print battery details and ACSwitch settings.

        -> `acs --info` will print battery level, charging state,
                        Automation state, disable threshold and
                        enable threshold

## Support

Please share your unease in [this Telegram group](https://t.me/joinchat/JUfXGwuAuzKxo5boALVf1w)
and I will serve you ASAP with required solutions.

## Legal

Thanks to VR25 @ xda-developers for providing their control files' database.

Copyright (c) 2019 Jaymin Suthar. All rights reserved.

See file NOTICE in project root for licensing information and more details.

## Changelog

#### 0.4.0.96

- Rebuild binary with new standards

#### 0.4.0.94

- Inline installer.sh with Magisk/module_installer.sh
- Update documentations

#### 0.3.1

- Internal code adjustments

#### 0.3

- Print success message after option is handled successfully
- Update internal code
- Update documentation
- Never check charger connection status
- Use only those triggers with an uevent

#### 0.2.1

- Fix 'Incorrect setup' errors even when configuring
- Fix 'Device not supported' errors when configuring
- Fix daemon blocking exit after killing via cmdline
- Some internal code improvements

#### 0.2

- Add support for the newer Magisk module template
- Fix device freezing after flashing from Magisk Manager
- Fix 'libc++_shared.so library not found' errors
- Fix empty or partial messages printed on terminal
- Fix read/writing on socket giving I/O errors
- Remove seteuid support, 'su' must be ran before 'acs'
- Stop logging to Android system, improve performance
- Code optimizations
- Update documentations

#### 0.1.1

- Update documentations

#### 0.1

- Initial release
