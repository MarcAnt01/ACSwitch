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

namespace Module
{
	const std::string ID = "ACSwitch";
	const std::string MOUNTPATH = "/data/adb/modules";
	const std::string STORAGE = MOUNTPATH + "/" + ID;

	const std::string SELF_NAME_CLIENT = "acs";
	const std::string SELF_NAME_DAEMON = "acsd";

	const std::string HELP =
		"Usage: `acs [<option> [<args>...]...]`\n"
		"\n"
		"Options:\n"
		"\n"
		"    [--toggle] <state: ON, OFF>\n"
		"\n"
		"        Toggle Automation status on or off.\n"
		"\n"
		"    [--update] <thr_disable: integer> <thr_enable: integer>\n"
		"\n"
		"        Set Automation disable threshold and enable threshold to\n"
		"        thr_disable and thr_enable respectively. Thresholds will\n"
		"        be reset if none were specified.\n"
		"\n"
		"    [--method] <format_str: (e|d)(%: integer|s|m|h)(threshold)>\n"
		"\n"
		"        Run a charging method (manually switch charging based on\n"
		"        format_str). Here, format_str may have...\n"
		"\n"
		"        ... (e|d)     defining if to enable or disable charging,\n"
		"        ... (%|s|m|h) defining if to run until a level is hit or\n"
		"                      for specified seconds, minutes or hours,\n"
		"        ...           and this is the threshold method runs for.\n"
		"\n"
		"        Only the element specifying charging state is necessary.\n"
		"\n"
		"    [--configure]\n"
		"\n"
		"        Configure ACSwitch. To properly configure ACSwitch, your\n"
		"        device must be charging or else it will likely fail with\n"
		"        an error.\n"
		"\n"
		"    [--daemon] <action: launch, kill>\n"
		"\n"
		"        Launch or kill the ACSwitch daemon. Remember, Automation\n"
		"        and charging methods, both depend on the daemon to work.\n"
		"\n"
		"    [--info]    Print battery information and ACSwitch settings.\n";

	[[noreturn]] void printHelp(const std::vector<std::string>& args) noexcept;
}
