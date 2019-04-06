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

#include "exception.h"

#include <cerrno>
#include <cstring>
#include <string>

using namespace std;

[[noreturn]] void Exception::_throw(const string& file, int line, const string& err) {
	string error = file.c_str() + ":"s + to_string(line) + ": " + err;
	if (errno != 0) {
		error += " ("s + strerror(errno) + ")"s;
	}
	throw Exception(error);
}

Exception::Exception(const string& what) noexcept {
	_what = what;
}

const char* Exception::what() const noexcept {
	return _what.c_str();
}
