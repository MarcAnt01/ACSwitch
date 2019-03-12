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

#include <android/log.h>
#include <iostream>

#include "logger.h"
#include "module.h"

using namespace std;

const char *Logger::LOGTAG = Module::ID.c_str();

void Logger::logE(const string &err) noexcept {
	cerr << err << endl;
	__android_log_write(ANDROID_LOG_ERROR, LOGTAG, err.c_str());
}
