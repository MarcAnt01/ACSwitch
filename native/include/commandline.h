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
#include <functional>
#include <string>
#include <vector>

using namespace std;

class Commandline {
	public:
		struct Option {
			string option;
			int argsMin;
			int argsMax;
			bool checkSetup;
			function<void (const vector<string> &args)> handler;
		};

	private:
		static const array<Option, 7> options;
		static const char **argvMain;

		static int optsIndex;
		static int argvIndex;
		static int argcMain;

		static bool setOptsIndexOf(const char *arg) noexcept;
		static bool populateArgs(vector<string> &args);

	public:
		static bool handleArgs(int argc, const char *argv[]) noexcept;
};
