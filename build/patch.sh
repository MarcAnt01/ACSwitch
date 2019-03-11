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

readonly DB_RAW=$BUILDDIR/switch.db-raw
readonly DB_SOURCE=$NATIVE/database.cc

readonly ELEMENT_BODY=\
"	{
		\"%s\",
		\"%s\",
		\"%s\",
		\"%s\"
	},"

readonly SOURCE_BODY=\
"vector<Database::Switch> Database::switch_ = { {
%s
} };"

function setprop {
	sed -i "s|^$1=.*|$1=$2|g" $3
}

function parsenode {
	set $1

	TRIGGER=$1
	POS_VAL=$2
	NEG_VAL=$3

	if [[ $1 != /sys/class/* && $1 != /sys/devices/* ]]; then
		UEVENT=/sys/class/power_supply/battery/uevent
	else
		UEVENT=$(dirname $1)/uevent
	fi

	[[ -n $NEG_VAL ]] && return 0 || return 1
}

print "Generating database source file"

ELEMENTS=""

while read LINE; do
	if ! parsenode "$LINE"; then
		abort "Raw database (switch.db-raw) is malformed, invalid entry: \"$LINE\""
	fi
	ELEMENTS+=$(printf "$ELEMENT_BODY\n" $UEVENT $TRIGGER $POS_VAL $NEG_VAL)
done < <(grep -Ev "^$|^#" $DB_RAW)

printf "$SOURCE_BODY\n" "$ELEMENTS" >>$DB_SOURCE
