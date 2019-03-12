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

#include <functional>
#include <string>
#include <vector>

using namespace std;

class Method {
	public:
		typedef struct {
			int mode;
			function<bool ()> startMethod;
			int thrType;
			int thrValue;
		} MethodInfo;

	private:
		static const int MODE_ENABLED;
		static const int MODE_DISABLED;

		static const int THR_TYPE_LEVELED;
		static const int THR_TYPE_TIMED;
		static const int THR_TYPE_NONE;

		static MethodInfo info;

		static bool parseAndPopulate(const string &fmtStr);

	public:
		static void parseAndRun(const vector<string> &args);
};
