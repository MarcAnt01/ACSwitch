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
		"    [--update] <thr_disable: int> <thr_enable: int>\n"
		"\n"
		"        Set Automation disable threshold and enable threshold to\n"
		"        thr_disable and thr_enable respectively. Thresholds will\n"
		"        be reset if none were specified.\n"
		"\n"
		"    [--method] <format_str: (e|d)(%: int|s|m|h)(threshold)>\n"
		"\n"
		"        Run a charging method. Here, format_str may have...\n"
		"\n"
		"        ... (e|d)     defines if enabling or disabling charging,\n"
		"        ... (%|s|m|h) defines if running until a level is hit or\n"
		"                      for specified seconds, minutes or hours,\n"
		"        ...           and this is the threshold method runs for.\n"
		"\n"
		"        Only the element specifying charging state is necessary.\n"
		"\n"
		"    [--configure]\n"
		"\n"
		"        Configure ACSwitch, while your device must be charging.\n"
		"\n"
		"    [--daemon] <action: launch, kill>\n"
		"\n"
		"        Launch or kill the ACSwitch daemon. Note that Automation\n"
		"        and charging methods, both depend on the daemon.\n"
		"\n"
		"    [--info]    Print battery information and ACSwitch settings.\n"
		"\n"
		"Note that no progress messages are printed to terminal. If you need to check for\n"
		"success, you can do so by checking return value of the process which must be '0'\n"
		"on success.\n";

	[[noreturn]] void printHelp(const std::vector<std::string>& args) noexcept;
}
