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

readonly PROJECT=$(realpath $(dirname $BASH_SOURCE))

readonly NATIVE=$PROJECT/native
readonly MODULE=$PROJECT/module

readonly TOOLSPATH=$PROJECT/tools
readonly BUILDDIR=$PROJECT/build
readonly BUILDER=$BUILDDIR/build.sh

function abort {
	echo >&2 -e "$SCRIPT_NAME: \e[01;33mERROR\e[0m: \e[01;31m$1\e[0m"
	if [[ -n $CLEANER ]]; then
		source $CLEANER
	fi
	exit 1
}

if [[ -z $ANDROID_NDK_HOME ]]; then
	abort "Please export Android NDK path to ANDROID_NDK_HOME"
fi
if ! command -v zip >/dev/null 2>&1; then
	abort "Please install package zip to compress module code"
fi

source $BUILDER

echo -e ""
echo -e "\e[01;32mOutput zip file: $OUTZIP\e[0m"
echo -e ""
echo -e "\e[01;32mIf you had made any changes to the original sources that could be benificial to\e[0m"
echo -e "\e[01;32mothers as well, please consider creating a Pull Request with your change/patches.\e[0m"
