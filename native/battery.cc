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

#include <chrono>
#include <fstream>
#include <libgen.h>
#include <thread>

#include "battery.h"
#include "config.h"
#include "exception.h"
#include "shared.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

const array<string, 2> Battery::BATTERY_SUBSYSTEMS = { { "battery", "Battery" } };
const array<string, 2> Battery::AC_SUBSYSTEMS = { { "ac", "AC" } };
const array<string, 2> Battery::USB_SUBSYSTEMS = { { "usb", "USB" } };

const string Battery::CAPACITY_EVENT = "POWER_SUPPLY_CAPACITY";
const string Battery::ONLINE_EVENT = "POWER_SUPPLY_ONLINE";
const string Battery::STATUS_EVENT = "POWER_SUPPLY_STATUS";

const string Battery::ONLINE_CONNECTED = "1";
const string Battery::STATUS_CHARGING = "Charging";

string Battery::getEvent(const array<string, 2> &subsystems, const string &event) {
	string uevent = Config::getUevent();

	for (const string &subsystem : subsystems) {
		uevent = dirname(dirname(uevent.c_str())) + subsystem + "/uevent";

		if (Shared::fileExists(uevent)) {
			return Shared::getProperty(event, uevent);
		}
	}
	throw("Setup is incorrect, please configure again");
}

string Battery::getEvent(const string &event) {
	return getEvent(BATTERY_SUBSYSTEMS, event);
}

void Battery::writeTrigger(const string &val) {
	const string trig = Config::getTrigger();
	ofstream trigger(trig, ios::out | ios::trunc);

	if (!trigger.is_open()) {
		throw("Could not open file: " + trig);
	} else {
		trigger << val << endl;
		sleep_for(seconds(1));
	}
}

string Battery::getCapacity() {
	return getEvent(CAPACITY_EVENT);
}

string Battery::getStatus() {
	return getEvent(STATUS_EVENT);
}

int Battery::getLevel() {
	return stoi(getCapacity());
}

bool Battery::isPowered() {
	const string usbOnlineVal = getEvent(USB_SUBSYSTEMS, ONLINE_EVENT);
	const string acOnlineVal = getEvent(AC_SUBSYSTEMS, ONLINE_EVENT);

	return usbOnlineVal == ONLINE_CONNECTED || acOnlineVal == ONLINE_CONNECTED;
}

bool Battery::isCharging() {
	return getStatus() == STATUS_CHARGING;
}

void Battery::startCharging() {
	writeTrigger(Config::getPosVal());
}

void Battery::stopCharging() {
	writeTrigger(Config::getNegVal());
}

void Battery::startChargingSafely() {
	if (isPowered() && !isCharging()) {
		startCharging();
	}
}

void Battery::stopChargingSafely() {
	if (isPowered() && isCharging()) {
		stopCharging();
	}
}