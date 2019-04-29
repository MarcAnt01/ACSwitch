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

namespace Module {
	const std::string ID = "ACSwitch";
	const std::string MOUNTPATH = "/data/adb/modules";
	const std::string STORAGE = MOUNTPATH + "/" + ID;

	const std::string SELF_NAME_CLIENT = "acs";
	const std::string SELF_NAME_DAEMON = "acsd";

	const std::string HELP =
		"Usage: `acs [<option> [<args>...]...]`\n"
		"\n"
		"[--toggle] <state>\n"
		"\n"
		"    Toggles Automation on or off.\n"
		"    <state> can be either 'ON' or 'OFF'.\n"
		"\n"
		"    -> `acs --toggle ON`  will toggle Automation on\n"
		"    -> `acs --toggle OFF` will toggle Automation off\n"
		"\n"
		"[--update] <thr_disable> <thr_enable>\n"
		"\n"
		"    Updates Automation disable threshold and enable threshold,\n"
		"    resets them to defaults if no values were specified.\n"
		"    <thr_disable> and <thr_enable> must be integers.\n"
		"\n"
		"    -> `acs --update 90 80` will set disable threshold to 90\n"
		"                            and enable threshold to 80\n"
		"    -> `acs --update`       will reset thresholds (70 60)\n"
		"\n"
		"[--method] <format_str>\n"
		"\n"
		"    Run a method based on format string <format_str>.\n"
		"    Here, format string must follow the pattern:\n"
		"        (e|d)(%|s|m|h)(threshold: int)\n"
		"\n"
		"    where...\n"
		"    ... (e|d)     defines if enabling or disabling charging,\n"
		"    ... (%|s|m|h) defines if seeking level or time interval,\n"
		"    ...           and this is the value of threshold.\n"
		"\n"
		"    -> `acs --method es60` will enable charging for 60 seconds\n"
		"    -> `acs --method d%40` will disable charging until 40%\n"
		"    -> `acs --method em30` will enable charging for 30 minutes\n"
		"\n"
		"[--configure]\n"
		"\n"
		"    Configure ACSwitch, device must be charging concurrently.\n"
		"    This task is required each time you change kernel or\n"
		"    update ACSwitch.\n"
		"\n"
		"    -> `acs --configure` will configure ACSwitch\n"
		"\n"
		"[--daemon] <action>\n"
		"\n"
		"    Launches or kills the daemon.\n"
		"    <action> can be either 'launch' or 'kill'.\n"
		"\n"
		"    -> `acs --daemon launch` will launch the daemon\n"
		"    -> `acs --daemon kill`   will kill the daemon\n"
		"\n"
		"[--info]\n"
		"\n"
		"    Print battery details and ACSwitch settings.\n"
		"\n"
		"    -> `acs --info` will print battery level, charging state,\n"
		"                    Automation state, disable threshold and\n"
		"                    enable threshold\n";

	[[noreturn]] void printHelp(const std::vector<std::string>& args) noexcept;
}
