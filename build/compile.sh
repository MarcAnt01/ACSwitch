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

readonly BINDIR=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

readonly API_LEVEL=21

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly ARM_COMPILER=$BINDIR/$ARM_TRIPLE-clang++
readonly X86_COMPILER=$BINDIR/$X86_TRIPLE-clang++

readonly SOURCE=(
	$NATIVE/*.cc
)

readonly HEADER=(
	-I$NATIVE/include
)

readonly CFLAGS=(
	-O2 -flto -fno-rtti -fomit-frame-pointer -fuse-ld=lld
)

readonly LDLIBS=(
	-llog -lsocket++
)

function compile {
	$1 ${SOURCE[@]} ${HEADER[@]} ${CFLAGS[@]} -L$MODULE/$2/lib ${LDLIBS[@]} -s -o $MODULE/$2/xbin/acs

	if (($? != 0)); then
		abort "Compile command failed"
	fi
}

print "Compiling acs binary for arm"
compile $ARM_COMPILER arm

print "Compiling acs binary for x86"
compile $X86_COMPILER x86
