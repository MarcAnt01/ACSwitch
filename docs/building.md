# Advanced Charging Switch

## Advanced Building

Building ACSwitch costs little, even if it restricts many aspects of platform
support for low-end architectures, but don't worry, here are some tips to
support them!

    Before reading onwards, take a look to these terms:

    compiler script                               <--- build/compile.sh
    libsocket++ libraries                         <--- native/lib/libsocket++_<arch>.a
    libraries folder                              <--- native/lib/

#### Host OS

As far as I am concerned, I haven't built ACSwitch on other platforms apart from Linux, I may
say that building on Macs should not require much modifications to scripts but
Windows, on the other hand, must take paths converted for `Windows Subsystem for Linux`
and executables suffixed `.exe` extensions. Except that, everything will work
great!

#### Target API

To target any NDK supported API, update `API_LEVEL` variable in compiler script.

#### Target architectures

To target 64-bit platforms, update `ARM_TRIPLE` and `X86_TRIPLE` in compiler script
recursively and replace libsocket++ libraries with their 64-bit builds.

To target other architectures, add calls to `compile` function in compiler script
with appropriate arguments, add a compile of libsocket++ in libraries folder and
update `module/META-INF/com/google/android/update-binary` correspondingly.

#### Older NDK versions

Building with older NDKs should require only changes as with for 64-bit platforms.
Keep in mind that the native part of ACSwitch complies with C++17, if your NDK doesn't
support it, you will need to transform the code to C++14 or C++11.
