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

readonly INSTALLER_SCRIPT=$MODULE/META-INF/com/google/android/update-binary

readonly DB_RAW=$BUILDDIR/switch.db-raw
readonly DB_SOURCE=$CORE/database.cc

readonly SOURCE_BODY=\
"vector<Database::ControlFile> Database::controlFiles = { {
%s
} };"

readonly ELEMENT_BODY=\
"	{
		\"%s\",
		\"%s\",
		\"%s\",
		\"%s\"
	},"

function setprop {
	sed -i "s|^$1=.*|$1=$2|g" $3
}

function parsenode {
	set $1
	if [[ $1 != /sys/class/* && $1 != /sys/devices/* ]]; then
		EVENTS=/sys/class/power_supply/battery/uevent
	else
		EVENTS=$(dirname $1)/uevent
	fi
	NODE=$1
	VAL_ON=$2
	VAL_OFF=$3
	[[ -n $VAL_OFF ]] && return 0 || return 1
}

setprop MIN_API $API_LEVEL $INSTALLER_SCRIPT

print "Generating database source file"

ELEMENTS=""

while read LINE; do
	if ! parsenode "$LINE"; then
		abort "Raw database is malformed, invalid entry: \"$LINE\""
	fi
	ELEMENTS+=$(printf "$ELEMENT_BODY\n" $EVENTS $NODE $VAL_ON $VAL_OFF)
done < <(grep -Ev "^$|^#" $DB_RAW)

printf "$SOURCE_BODY\n" "$ELEMENTS" >>$DB_SOURCE
