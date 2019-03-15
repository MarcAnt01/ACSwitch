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
#include <iostream>

#include "logger.h"
#include "module.h"

using namespace std;
using namespace chrono;

ofstream Logger::logfile(Module::STORAGE + "/.logs");

char * Logger::getCurrentTime() noexcept {
	time_t currentTime = system_clock::to_time_t(system_clock::now());
	char *currentTimeFull = ctime(&currentTime);
	currentTimeFull[strlen(currentTimeFull) - 1] = '\0';
	return currentTimeFull;
}

void Logger::logE(const string &err) noexcept {
	cerr << err << endl;
	logfile << getCurrentTime() << ": " << err << endl;
}
