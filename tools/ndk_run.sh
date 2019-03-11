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

readonly ARM_TRIPLE=arm-linux-androideabi
readonly X86_TRIPLE=i686-linux-android

readonly ARCH=$1
readonly TOOL=$2

shift 2

function abort {
	echo >&2 -e "\n\e[01;33mERROR\e[0m: \e[01;31m$1\e[0m\n"
	exit 1
}

mkdir $WORKDIR 2>/dev/null
if ! cd $WORKDIR; then
	abort "Could not change current working directory to $WORKDIR"
fi

case $ARCH in
	arm) $ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$ARM_TRIPLE-$TOOL $@ ;;
	x86) $ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/$X86_TRIPLE-$TOOL $@ ;;
esac

if (($? != 0)); then
	abort "Command \`$TOOL $*\` failed"
fi
