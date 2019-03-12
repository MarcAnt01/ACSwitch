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
#include "config.h"
#include "daemon.h"
#include "database.h"
#include "exception.h"
#include "setup.h"
#include "shared.h"

const string Setup::DUMMY_SWITCH = "dummyValue";

void Setup::setSwitch(const Database::Switch &switch_) {
	Config::setUevent(switch_.uevent);
	Config::setTrigger(switch_.trigger);
	Config::setPosVal(switch_.posVal);
	Config::setNegVal(switch_.negVal);
}

bool Setup::configGood() {
	return Shared::fileExists(Config::getUevent()) && Shared::fileExists(Config::getTrigger());
}

void Setup::checkOrDie() {
	if (!configGood()) {
		throw("Setup is incomplete, please configure first");
	}
	if (!Daemon::isRunning()) {
		throw("The daemon is not running, launch it first");
	}
}

void Setup::configureSwitch(const vector<string> &args) {
	for (const Database::Switch &switch_ : Database::getSwitches()) {
		setSwitch(switch_);

		if (Battery::isPowered() && Battery::isCharging()) {
			Battery::stopCharging();
			if (!Battery::isPowered() || Battery::isCharging()) {
				Battery::startCharging();
			} else {
				Battery::startCharging();
				if (Battery::isCharging()) {
					return;
				}
			}
		}
	}
	setSwitch({
		DUMMY_SWITCH,
		DUMMY_SWITCH,
		DUMMY_SWITCH,
		DUMMY_SWITCH
	});
	throw("Your device is unfortunately not supported :(");
}
