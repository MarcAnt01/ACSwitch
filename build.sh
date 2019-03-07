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

readonly API_LEVEL=21

readonly OUTDIR=$PROJECT/out

readonly LOGFILE=$OUTDIR/build.log

readonly TOOLSPATH=$PROJECT/tools
readonly BUILDDIR=$PROJECT/build
readonly BUILDER=$BUILDDIR/build.sh

mkdir $OUTDIR 2>/dev/null
exec 3>&2 2>$LOGFILE

function abort {
	echo >&3 -e "\n$SCRIPT_NAME: \e[01;33mERROR\e[0m: \e[01;31m$1\e[0m\n"
	if [[ -n $CLEANER ]]; then
		source $CLEANER
	fi
	exit 1
}

if [[ -z $ANDROID_NDK_HOME ]]; then
	abort "Please export Android NDK path to ANDROID_NDK_HOME"
fi
if ! command -v zip >/dev/null; then
	abort "Please install package zip to compress module code"
fi

echo -e ""

source $BUILDER

echo -e ""
echo -e "Output zip file: \e[01;32m$OUTZIP\e[0m"
echo -e ""
echo -e "\e[01;35mIf you had made any changes to the original sources that could be benificial to\e[0m"
echo -e "\e[01;35mothers as well, please create a Pull Request back with your change/patches.\e[0m"
echo -e ""
