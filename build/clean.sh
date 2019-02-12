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

readonly NATIVE_FILES=(
	$DB_HEADER
	$DB_SOURCE
)

readonly MODULE_FILES=(
	$BINDIR/*
)

print "Cleaning up"

(
	rm -rf $TEMPZIP

	git --work-tree $NATIVE --git-dir $PROJECT/.git/modules/native checkout -- ${NATIVE_FILES[@]}
	git --work-tree $MODULE --git-dir $PROJECT/.git/modules/module checkout -- ${MODULE_FILES[@]}

	git --work-tree $PROJECT --git-dir $PROJECT/.git checkout devel
	git --work-tree $NATIVE --git-dir $PROJECT/.git/modules/native checkout devel
	git --work-tree $MODULE --git-dir $PROJECT/.git/modules/module checkout devel
) >/dev/null 2>&1
