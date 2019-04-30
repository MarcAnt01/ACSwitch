# Advanced Charging Switch

## Advanced Building

Building ACSwitch costs little, but it though restricts many aspects of platform
support for low end architectures. Don't worry though, here are some tips to
support them!

    Before reading onwards, know these terms:

    compiler script                               <--- build/compile.sh
    libsocket++ libraries                         <--- native/lib/libsocket++_<arch>.a
    libraries folder                              <--- native/lib/

#### Host OS

Though I haven't personally built ACSwitch on platforms other than Linux, I may
say that building on Macs should not require much modifications to scripts but
Windows, on the other hand, must take paths converted for `Windows Subsystem for Linux`
and executables suffixed `.exe` extensions. Other than these, everything will work
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
