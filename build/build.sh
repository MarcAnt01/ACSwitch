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

readonly ANDROID_NDK=$ANDROID_NDK_HOME

readonly CONFIGURATOR=$BUILDDIR/configure.sh
readonly COMPILER=$BUILDDIR/compile.sh
readonly PACKER=$BUILDDIR/pack.sh
readonly CLEANER=$BUILDDIR/clean.sh

function print {
	echo -e "- \e[01;33m$1\e[0m"
}

function getprop {
	sed -n "s/^$1=//p" $2
}

readonly VERSION=$(getprop version $MODULE/module.prop)
readonly CODE=$(getprop versionCode $MODULE/module.prop)

(
	git --work-tree $PROJECT --git-dir $PROJECT/.git checkout master
	git --work-tree $NATIVE --git-dir $PROJECT/.git/modules/native checkout master
	git --work-tree $MODULE --git-dir $PROJECT/.git/modules/module checkout master
) 2>/dev/null

source $CONFIGURATOR
source $COMPILER
source $PACKER
source $CLEANER
