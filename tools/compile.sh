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

readonly ANDROID_NDK=/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK

readonly OUTDIR=$(dirname $(dirname $BASH_SOURCE))/temp

readonly API_LEVEL=21

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly COMPILER_ARM=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$ARM_TRIPLE-clang++
readonly COMPILER_X86=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$X86_TRIPLE-clang++

function abort {
	echo >&2 "ERROR: $1"
	exit 1
}

function compile {
	local COMPILER=$1
	local ARCH=$2
	shift 2

	$COMPILER $@ -O2 -flto -fno-rtti -fomit-frame-pointer -fuse-ld=lld -fPIC -s -o $OUTDIR/a.out.$ARCH

	if (($? != 0)); then
		abort "Compilation failed"
	fi
}

mkdir $OUTDIR 2>/dev/null

echo "Compiling a.out for arm"
compile $COMPILER_ARM arm $@

echo "Compiling a.out for x86"
compile $COMPILER_X86 x86 $@
