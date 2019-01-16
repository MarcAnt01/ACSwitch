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

readonly OUTDIR=$PROJECT/out

readonly ZIPSIGNER=$TOOLSPATH/zipsigner.jar

readonly ZIPNAME=ACSwitch-$VERSION-$CODE-stable

readonly OUTZIP=$OUTDIR/$ZIPNAME-signed.zip
readonly TEMPZIP=$OUTDIR/$ZIPNAME.tempfile

function makezip {
	local ZIPFILE=$1
	local MODDIR=$2

	cd $MODDIR || abort "Could not change directory to $MODDIR"

	find . | while read FILE; do
		if [[ $FILE != ./.git/* ]]; then
			if [[ $FILE != ./.git ]]; then
				zip -u9q $ZIPFILE $FILE
			fi
		fi
	done
}

function signzip {
	java -jar $ZIPSIGNER $1 $2
}

rm -f $TEMPZIP $OUTZIP
mkdir $OUTDIR 2>/dev/null

print "Packing flashable zip"
makezip $TEMPZIP $MODULE

print "Signing the zip file"
signzip $TEMPZIP $OUTZIP
