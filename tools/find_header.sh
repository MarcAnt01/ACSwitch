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

readonly INCLUDE_PATH_ALL=(
	/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/c++/v1
	/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/local/include
	/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK/toolchains/llvm/prebuilt/linux-x86_64/lib64/clang/8.0.2/include
	/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/sysroot/usr/include/aarch64-linux-android
	/media/sjaymin/__SHARED_K__/Development/IDE/Android_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/sysroot/usr/include
)

readonly HEADER_NAME=$1

HEADERS_FOUND=()

while read HEADER; do
	HEADERS_FOUND+=($HEADER)
done < <(find ${INCLUDE_PATH_ALL[@]} -type f -name $HEADER_NAME 2>/dev/null)

if ((${#HEADERS_FOUND[@]} > 0)); then
	code --new-window ${HEADERS_FOUND[@]}
fi
