#!/usr/bin/env bash

# Copyright (c) 2019 Jaymin Suthar. All rights reserved.
#
# This file is part of "Advanced Charging Switch (ACSwitch)".
#
# ACSwitch is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, only version 3 of the License.
#
# ACSwitch is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ACSwitch.  If not, see <https://www.gnu.org/licenses/>.

SCRIPT_NAME=$(basename $BASH_SOURCE)

readonly BINDIR=$MODULE/bin

readonly COMPILER_BINDIR=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly COMPILER_ARM=$COMPILER_BINDIR/$ARM_TRIPLE-clang++
readonly COMPILER_X86=$COMPILER_BINDIR/$X86_TRIPLE-clang++

function compile {
	$1 $NATIVE/*.cc -I$INCLUDE_PATH -O2 -llog -s -o $BINDIR/acs_$2

	if (($? != 0)); then
		abort "Compilation failed"
	fi
}

print "Compiling acs binary for arm"
compile $COMPILER_ARM arm

print "Compiling acs binary for x86"
compile $COMPILER_X86 x86
