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

readonly ANDROID_NDK=$ANDROID_NDK_HOME

readonly MODINFO=$MODULE/module.prop

readonly PATCHER=$BUILDDIR/patch.sh
readonly COMPILER=$BUILDDIR/compile.sh
readonly PACKER=$BUILDDIR/pack.sh
readonly CLEANER=$BUILDDIR/clean.sh

function print {
	echo -e "\e[01;34m- $1\e[0m"
}

function getprop {
	sed -n "s/^$1=//p" $2
}

function setprop {
	sed -i "s/^$1=.*/$1=$2/g" $3
}

readonly VERSION=$(getprop version $MODINFO)
readonly CODE=$(($(getprop versionCode $MODINFO) + 1))

setprop versionCode $CODE $MODINFO
sed -i "s/__VERSION_CODE__/$CODE/" $NATIVE/module.cc

source $PATCHER
source $COMPILER
source $PACKER
source $CLEANER
