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

readonly ALL_HEADER=(
	$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/c++/v1
	$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/local/include
	$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/lib64/clang/8.0.2/include
	$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/arm-linux-androideabi
	$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include
)

HEADERS_FOUND=()

while read HEADER; do
	HEADERS_FOUND+=($HEADER)
done < <(find ${ALL_HEADER[@]} -type f -name $1 2>/dev/null)

if ((${#HEADERS_FOUND[@]} > 0)); then
	code --new-window ${HEADERS_FOUND[@]}
fi
