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

#include <mutex>
#include <string>
#include <vector>

using namespace std;

class Daemon {
	private:
		static const int REQUEST_CHECK;
		static const int REQUEST_KILL;

		static const int REQUEST_AUTOMATE;
		static const int REQUEST_ENABLE;
		static const int REQUEST_DISABLE;

		static const int RET_VAL_POSITIVE;
		static const int RET_VAL_NEGATIVE;

		static bool IAmKilled;
		static int switchMode;
		static mutex switchLock;

		static int getSwitchMode();
		static void setSwitchMode(int val);

		static void handleRequest(int req);
		static void handleSwitch(int mode);
		static void clientHandler() noexcept;
		static void switchHandler() noexcept;

	public:
		static bool isRunning();

		static void requestAutomating();
		static bool requestEnabling();
		static bool requestDisabling();

		static void handleArgs(const vector<string> &args);
		[[noreturn]] static void runServer() noexcept;
};
