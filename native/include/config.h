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

#include <string>
#include <vector>

using namespace std;

class Config {
	private:
		static const string SAVE_FILE;

		static const string AUTOMATION_KEY;
		static const string THR_DISABLE_KEY;
		static const string THR_ENABLE_KEY;

		static const string UEVENT_KEY;
		static const string TRIGGER_KEY;
		static const string POS_VAL_KEY;
		static const string NEG_VAL_KEY;

		static const string AUTOMATION_ENABLED;
		static const string AUTOMATION_DISABLED;
		static const string THR_DISABLE_DEF;
		static const string THR_ENABLE_DEF;

		static string getConfig(const string &key);
		static void setConfig(const string &key, const string &val);

	public:
		static bool isAutomated();
		static int getThrDisable();
		static int getThrEnable();

		static string getUevent();
		static string getTrigger();
		static string getPosVal();
		static string getNegVal();

		static void setUevent(const string &val);
		static void setTrigger(const string &val);
		static void setPosVal(const string &val);
		static void setNegVal(const string &val);

		static void toggleAutomation(const vector<string> &args);
		static void updateThresholds(const vector<string> &args);
};
