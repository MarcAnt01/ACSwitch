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

#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

#include "battery.h"
#include "config.h"
#include "exception.h"
#include "module.h"
#include "utility.h"

using namespace std;

bool Utility::xfork() {
	pid_t child = fork();
	switch (child) {
		case -1: throw("Could not fork child");
		case 0: return false;
		default: return true;
	}
}

void Utility::execDaemon(const vector<string> &args) {
	if (!xfork()) {
		setsid();

		if (xfork()) {
			exit(EXIT_SUCCESS);
		} else {
			const char *argv[args.size() + 1];
			argv[args.size()] = nullptr;

			for (int i = 0; i < args.size(); i++) {
				argv[i] = args[i].c_str();
			}
			if (execvp(Module::SELF_NAME_CLIENT.c_str(), (char *const *) argv)) {
				throw("Could not exec process");
			}
		}
	}
}

void Utility::printInfo(const vector<string> &args) {
	cout << "Battery Information\n"
		<< "\n"
		<< "Level: " << Battery::getCapacity() << "\n"
		<< "State: " << Battery::getStatus() << "\n"
		<< "\n"
		<< Module::ID << " Settings\n"
		<< "\n"
		<< "Automation: " << (Config::isAutomated() ? "Enabled" : "Disabled") << "\n"
		<< "Disable threshold: " << Config::getThrDisable() << "\n"
		<< "Enable threshold: " << Config::getThrEnable() << endl;
}
