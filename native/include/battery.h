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

#pragma once

#include <array>
#include <string>

using namespace std;

class Battery {
	private:
		static const array<string, 2> BATTERY_SUBSYSTEMS;
		static const array<string, 2> AC_SUBSYSTEMS;
		static const array<string, 2> USB_SUBSYSTEMS;

		static const string CAPACITY_EVENT;
		static const string ONLINE_EVENT;
		static const string STATUS_EVENT;

		static const string ONLINE_CONNECTED;
		static const string STATUS_CHARGING;

	private:
		static string getEvent(const array<string, 2> &subsystems, const string &event);
		static string getEvent(const string &event);
		static void writeTrigger(const string &val);

	public:
		static string getCapacity();
		static string getStatus();

		static int getLevel();
		static bool isPowered();
		static bool isCharging();

		static void startCharging();
		static void stopCharging();
		static void startChargingSafely();
		static void stopChargingSafely();
};
