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

function xgit {
	if ! cd $1; then
		abort "Could not change current working directory to $1"
	fi
	shift
	git "$@" >/dev/null
}

function reset {
	xgit $1 checkout -- .
	if [[ -n $2 && $2 == true ]]; then
		xgit $1 reset --soft HEAD~
	fi
}

case $1 in
	!)
		reset $MODULE  $RESET_MODULE
		reset $PROJECT $RESET_PROJECT
	;;
	*)
		RESET_MODULE=false
		RESET_PROJECT=false

		if xgit $MODULE  commit --signoff -a -m "Save state"; then
			RESET_MODULE=true
		fi
		if xgit $PROJECT commit --signoff -a -m "Save state"; then
			RESET_PROJECT=true
		fi
	;;
esac
