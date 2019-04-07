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

class Exception : public std::exception {
	public:
		[[noreturn]] static void _throw(const std::string& file, int line, const std::string& err);

		Exception(const std::string& what) noexcept;
		~Exception() noexcept {}
		const char* what() const noexcept;

	private:
		std::string _what;
};

#define throw(err) Exception::_throw(__FILE__, __LINE__, (err))
