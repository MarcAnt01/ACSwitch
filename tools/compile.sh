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

readonly WORKDIR=$(dirname $(dirname $BASH_SOURCE))/temp

readonly ANDROID_NDK=/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK

readonly API_LEVEL=21

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly ARCH=$1

shift

function abort {
	echo >&2 -e "\n\e[01;33mERROR\e[0m: \e[01;31m$1\e[0m\n"
	exit 1
}

mkdir $WORKDIR 2>/dev/null
if ! cd $WORKDIR; then
	abort "Could not change current working directory to $WORKDIR"
fi

case $ARCH in
	arm) $ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$ARM_TRIPLE-clang++ $@ ;;
	x86) $ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$X86_TRIPLE-clang++ $@ ;;
esac

if (($? != 0)); then
	abort "Command \`clang++ $*\` failed"
fi
