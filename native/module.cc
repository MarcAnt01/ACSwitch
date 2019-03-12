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

#include <iostream>

#include "module.h"

using namespace std;

const string Module::ID = "ACSwitch";
const string Module::MOUNTPATH = "/data/adb/modules";
const string Module::STORAGE = MOUNTPATH + "/" + ID;

const string Module::SELF_NAME_CLIENT = "acs";
const string Module::SELF_NAME_DAEMON = "acsd";

const string Module::HELP =
"Usage: `acs [<option> [<args>...]...]`\n"
"\n"
"Options:\n"
"\n"
"        [--toggle] <state: ON, OFF>\n"
"\n"
"                        Toggle Automation on or off. See 'Description' above for\n"
"                        details about Automation.\n"
"\n"
"        [--update] <thr_disable: 0 <= i <= 100> <thr_enable: 0 <= i <= 100>\n"
"\n"
"                        Set Automation disable threshold and enable threshold to\n"
"                        thr_disable and thr_enable respectively. Omitting values\n"
"                        will reset them to their defaults.\n"
"\n"
"        [--method] <format_str: (e|d)(%: 0 <= i <= 100|s|m|h)(threshold)>\n"
"\n"
"                        Run a charging method, manually switch charging based on\n"
"                        format_str. Here, format string has elements...\n"
"\n"
"                        ... (e|d)     defines if enabling or disabling charging.\n"
"                        ... (%|s|m|h) defines if running based on time or level.\n"
"                        ...           and last is the threshold method runs for.\n"
"\n"
"                        Second and third elements are optional, they're supposed\n"
"                        to keep method running up until given condition is met.\n"
"\n"
"        [--configure]\n"
"\n"
"                        Configure ACSwitch. To determine whether found switch is\n"
"                        working correctly, device must be charging while running\n"
"                        this option. This process may take a few minutes.\n"
"\n"
"        [--daemon] <action: launch, kill>\n"
"\n"
"                        Launch or kill the ACSwitch daemon.\n"
"\n"
"        [--info]        Print battery information and ACSwitch settings.\n";

[[noreturn]] void Module::printHelp(const vector<string> &args) noexcept {
	cerr << HELP << endl;
	exit(EXIT_FAILURE);
}
