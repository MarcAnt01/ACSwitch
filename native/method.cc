/* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
 *
 * This file is part of "Advanced Charging Switch (ACSwitch)".
 *
 * ACSwitch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, only version 3 of the License.
 *
 * ACSwitch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ACSwitch.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "battery.h"
#include "daemon.h"
#include "exception.h"
#include "method.h"
#include "sanity.h"

#include <chrono>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;
using namespace chrono;
using namespace this_thread;

static const int MODE_ENABLED = 1;
static const int MODE_DISABLED = 2;

static const int THR_TYPE_LEVELED = 1;
static const int THR_TYPE_TIMED = 2;
static const int THR_TYPE_NONE = 3;

static Method::MethodInfo info;

static bool parseAndPopulate(const string& fmtStr) {
	switch (fmtStr[0]) {
		case 'e':
			info.mode = MODE_ENABLED;
			info.startMethod = Daemon::requestEnabling;
			break;
		case 'd':
			info.mode = MODE_DISABLED;
			info.startMethod = Daemon::requestDisabling;
			break;
		default: return false;
	}

	switch (fmtStr.size()) {
		case 2:
			return false;
		case 1: {
			info.thrType = THR_TYPE_NONE;
			return true;
		}
	}

	switch (fmtStr[1]) {
		case '%':
			info.thrType = THR_TYPE_LEVELED;
			info.thrValue = Sanity::toLevel(fmtStr.substr(2));
			break;
		case 's':
			info.thrType = THR_TYPE_TIMED;
			info.thrValue = stoi(fmtStr.substr(2));
			break;
		case 'm':
			info.thrType = THR_TYPE_TIMED;
			info.thrValue = stoi(fmtStr.substr(2)) * 60;
			break;
		case 'h':
			info.thrType = THR_TYPE_TIMED;
			info.thrValue = stoi(fmtStr.substr(2)) * 3600;
			break;
		default: return false;
	}
	return true;
}

void Method::parseAndRun(const vector<string>& args) {
	if (!parseAndPopulate(args[0])) {
		throw("Invalid format string: " + args[0]);
	}

	if (!info.startMethod()) {
		throw("Another method is already running");
	}

	if (info.thrType == THR_TYPE_TIMED) {
		sleep_for(seconds(info.thrValue));

	} else if (info.thrType == THR_TYPE_LEVELED) {
		if (
				(Battery::getLevel() >= info.thrValue && info.mode == MODE_ENABLED)
			|| (Battery::getLevel() <= info.thrValue && info.mode == MODE_DISABLED)
		) {
			throw("Unreachable target level: " + args[0].substr(2));
		}

		while (Battery::getLevel() != info.thrValue) {
			sleep_for(seconds(Sanity::SLEEP_DELAY));
		}
	} else {}
	Daemon::requestAutomating();
}
