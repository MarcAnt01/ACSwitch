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
readonly OUTBIN=$BINDIR/acs_\$1

readonly NDK_BINDIR=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

readonly API_LEVEL=21

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly ARM_COMPILER=$NDK_BINDIR/$ARM_TRIPLE-clang++
readonly X86_COMPILER=$NDK_BINDIR/$X86_TRIPLE-clang++

readonly CFLAGS=(
	-O2 -fno-rtti -fomit-frame-pointer -flto
)

readonly LDLIBS=(
	-L$NATIVE/lib -lsocket++_\$1 -static
)

function compile {
	eval $2 *.cc -I$INCLUDE ${CFLAGS[@]} ${LDLIBS[@]} -s -o $OUTBIN

	if (($? != 0)); then
		abort "Compile command failed"
	fi
}

if ! cd $NATIVE; then
	abort "Could not change current working directory to $NATIVE"
fi

print "Compiling acs binary for arm"
compile arm $ARM_COMPILER

print "Compiling acs binary for x86"
compile x86 $X86_COMPILER
