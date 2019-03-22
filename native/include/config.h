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

namespace Config {
	bool isAutomated();
	int getThrDisable();
	int getThrEnable();

	string getUevent();
	string getTrigger();
	string getPosVal();
	string getNegVal();

	void setUevent(const string &val);
	void setTrigger(const string &val);
	void setPosVal(const string &val);
	void setNegVal(const string &val);

	void toggleAutomation(const vector<string> &args);
	void updateThresholds(const vector<string> &args);
}
